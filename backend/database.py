from questdb.ingress import Sender, TimestampNanos 
import pytz

conf = "http::addr=localhost:9000;username=admin;password=quest;"



def append_row(temperature,humidity):
    with Sender.from_conf(conf) as sender:
        sender.row(
            'sensors',
            symbols={'id': 'device'},
            columns={'temperature': temperature, 'humidity': humidity},
            at=TimestampNanos.now())
        sender.flush()

