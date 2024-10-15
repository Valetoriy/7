import paho.mqtt.client as mqtt
from matplotlib import pyplot
from matplotlib.animation import FuncAnimation
import numpy

x_data = []
counter = 0
temp_data, hum_data, ms_data, us_data = [], [], [], []

fig, axs = pyplot.subplots(2, 2)
temp, = axs[0, 0].plot(x_data, temp_data, 'b-')
axs[0, 0].set_title('Температура')
hum, = axs[0, 1].plot(x_data, hum_data, 'g-')
axs[0, 1].set_title('Влажность')
ms, = axs[1, 0].plot(x_data, ms_data, 'r-')
axs[1, 0].set_title('Задержка при измерении, мс')
us, = axs[1, 1].plot(x_data, us_data, '-', color='orange')
axs[1, 1].set_title('Задержка при измерении, μс')

client = mqtt.Client()

def update(frame):
    client.loop()
    temp.set_data(x_data, temp_data)
    hum.set_data(x_data, hum_data)
    ms.set_data(x_data, ms_data)
    us.set_data(x_data, us_data)
    for i in range(0, 2):
        for j in range(0, 2):
            axs[i, j].relim()
            axs[i, j].autoscale_view()
    if len(x_data) >= 40:
        x_data.pop(0)
        temp_data.pop(0)
        hum_data.pop(0)
        ms_data.pop(0)
        us_data.pop(0)
    return axs,

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print('Успешное подключение')
        client.subscribe('iotl4/esp_srvc')
    else:
        print(f'Ошибка подключения: {rc}')

def on_message(client, userdata, msg):
    global counter
    x_data.append(counter)
    counter += 1
    data = numpy.fromstring(msg.payload.decode(), dtype=float, sep=' ')
    temp_data.append(data[0])
    hum_data.append(data[1])
    ms_data.append(data[2])
    us_data.append(data[3])

def run_mqtt_service():
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect('ЛОКАЛЬНЫЙ IP', 1883)

    animation = FuncAnimation(fig, update, interval=100, cache_frame_data=False)
    pyplot.show()


run_mqtt_service()
