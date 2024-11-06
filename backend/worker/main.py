import paho.mqtt.client as mqtt
import database , json , pytz

bkk_timezone = pytz.timezone('Asia/Bangkok')

def on_connect(client, userdata, flags, reason_code, properties):
    
    print(f"Connected with result code {reason_code}")
    client.subscribe("temp-hum-pj/send")

def on_message(client, userdata, msg):
    val = json.loads(msg.payload)
    database.append_row(val["temp"], val["hum"])
    print(val)

mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_connect = on_connect
mqttc.on_message = on_message

mqttc.connect("localhost", 1883, 60)

mqttc.loop_forever()
