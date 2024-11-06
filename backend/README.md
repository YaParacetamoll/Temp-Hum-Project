# Backend Guide
## รัน QuestDB Time Series Database (ทำก่อน)
```bash
cd backend/
docker-compose up
```
## รัน Woker สำหรับ Subscribe จาก Mqtt เข้า DB
ที่ main.py ให้ set broker ให้เรียบร้อย
```py
5| broker = "broker.hivemq.com"
```
ex
```diff
- broker = "broker.hivemq.com"
+ broker = "phycom.it.kmitl.ac.th"
```


ทำvenv -> activate -> ติดตั้งlibrary -> รัน `main.py` -> deactivate
```bash
python -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python main.py
deactivate
```
