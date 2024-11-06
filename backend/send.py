import paho.mqtt.client as mqtt
import json ,time , random



def on_connect(client, userdata, flags, reason_code, properties):
    #print(f"Connected with result code {reason_code}")
    #client.subscribe("242/send")
    pass

def on_message(client, userdata, msg):
    #print(msg.topic+" "+str(msg.payload))
    pass

mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_connect = on_connect
mqttc.on_message = on_message

# broker.hivemq.com
mqttc.connect("localhost", 1883, 60)

mqttc.loop_start()

while True:
    
    temperature = json.dumps({"temp":random.random()*100,"hum":random.random()*100})
    time.sleep(3)
    mqttc.publish("242/send", temperature)

mqttc.loop_stop()
