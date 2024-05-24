// This example demonstrates the ESP RainMaker with a standard Switch device.
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include "AppInsights.h"

#define DEFAULT_POWER_MODE true
const char *service_name = "PROV_1234";
const char *pop = "abcd1234";

// GPIO for push button, virtual device and light sensor
static int gpio_0 = 0;
static int gpio_switch = 16;
#define LIGHT_SENSOR_PIN 4

/* Variable for reading pin status*/
bool switch_state = true;

// The framework provides some standard device types like switch, lightbulb,
// fan, temperaturesensor.
static Switch *my_switch = NULL;
static Device *my_ldr = NULL;

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {
    case ARDUINO_EVENT_PROV_START:
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n",
                      service_name, pop);
        printQR(service_name, pop, "ble");
        break;
    case ARDUINO_EVENT_PROV_INIT:
        wifi_prov_mgr_disable_auto_stop(10000);
        break;
    case ARDUINO_EVENT_PROV_CRED_SUCCESS:
        wifi_prov_mgr_stop_provisioning();
        break;
    default:;
    }
}

void write_callback(Device *device, Param *param, const param_val_t val,
                    void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if (strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n",
                      val.val.b ? "true" : "false", device_name, param_name);
        switch_state = val.val.b;
        (switch_state == false) ? digitalWrite(gpio_switch, LOW)
        : digitalWrite(gpio_switch, HIGH);
        param->updateAndReport(val);
    }
}

//initialise counter
int i = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT_PULLUP);
    pinMode(gpio_switch, OUTPUT);
    digitalWrite(gpio_switch, DEFAULT_POWER_MODE);

    Node my_node;
    my_node = RMaker.initNode("ESP RainMaker Node");

    // Initialize switch device
    my_switch = new Switch("Switch", &gpio_switch);
    if (!my_switch) {
        return;
    }

    int ldrValue = map(analogRead(LIGHT_SENSOR_PIN),0,4095,0,100);

    // Initialize LDR
    my_ldr = new Device("Light Sensor", ESP_RMAKER_DEVICE_TEMP_SENSOR, NULL);
    if (!my_ldr) {
        return;
    }

    //Create custom light sensor
    my_ldr->addNameParam();
    my_ldr->assignPrimaryParam(my_ldr->getParamByName(ESP_RMAKER_DEF_POWER_NAME));

    Param brightness("Brightness", ESP_RMAKER_PARAM_TEMPERATURE, value(ldrValue), PROP_FLAG_READ | PROP_FLAG_TIME_SERIES);
    my_ldr->addParam(brightness);

    // Standard switch device
    my_switch->addCb(write_callback);

    // Add switch device to the node
    my_node.addDevice(*my_switch);
    my_node.addDevice(*my_ldr);

    // This is optional
    RMaker.enableOTA(OTA_USING_TOPICS);
    // If you want to enable scheduling, set time zone for your region using
    // setTimeZone(). The list of available values are provided here
    // https://rainmaker.espressif.com/docs/time-service.html
    RMaker.setTimeZone("Asia/Shanghai");
    //  Alternatively, enable the Timezone service and let the phone apps set the
    //  appropriate timezone
    RMaker.enableTZService();

    RMaker.enableSchedule();

    RMaker.enableScenes();
    // Enable ESP Insights. Insteads of using the default http transport, this function will
    // reuse the existing MQTT connection of Rainmaker, thereby saving memory space.
    //initAppInsights();

    RMaker.enableSystemService(SYSTEM_SERV_FLAGS_ALL, 2, 2, 2);

    RMaker.start();

    WiFi.onEvent(sysProvEvent);
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM,
                            WIFI_PROV_SECURITY_1, pop, service_name);
}

void loop()
{
  int ldrValue = map(analogRead(LIGHT_SENSOR_PIN),0,4095,0,100);

  // 10*500 = 5000, Update every 5 seconds
  if (i == 10) {
    my_ldr->updateAndReportParam("Brightness", ldrValue);
    i=0;
  }

  Serial.print("Raw LDR value = ");
  Serial.println(analogRead(LIGHT_SENSOR_PIN));
  Serial.print("Mapped LDR value = ");
  Serial.println(ldrValue);

    if (digitalRead(gpio_0) == LOW) {  // Push button pressed
        // Key debounce handling
        delay(100);
        int startTime = millis();
        while (digitalRead(gpio_0) == LOW) {
            delay(50);
        }
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
            // If key pressed for more than 10secs, reset all
            Serial.printf("Reset to factory.\n");
            RMakerFactoryReset(2);
        } else if ((endTime - startTime) > 3000) {
            Serial.printf("Reset Wi-Fi.\n");
            // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
            RMakerWiFiReset(2);
        } else {
            // Toggle device state
            switch_state = !switch_state;
            Serial.printf("Toggle State to %s.\n", switch_state ? "true" : "false");
            if (my_switch) {
                my_switch->updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,
                                                switch_state);
            }
            (switch_state == false) ? digitalWrite(gpio_switch, LOW)
            : digitalWrite(gpio_switch, HIGH);
        }
    }
  i++;
  delay(500);
}
