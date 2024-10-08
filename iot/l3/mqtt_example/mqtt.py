import paho.mqtt.client as mqtt
import random

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Успешное подключение")
        client.subscribe("iotl3/esp_srvc")
    else:
        print(f"Ошибка подключения: {rc}")

def on_message(client, userdata, msg):
    if random.randint(0, 1) == 1:
        client.publish("iotl3/srvc_esp", "1")
    else:
        alert_msg = "Попытка несанкционированного доступа!"
        print(alert_msg)
        client.publish("iotl3/srvc_phone", alert_msg)
        client.publish("iotl3/srvc_esp", "0")

def run_mqtt_service():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect("test.mosquitto.org", 1883)
    client.loop_forever()

run_mqtt_service()
