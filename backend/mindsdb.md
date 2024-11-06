# MindsDB

## Connect with QuestDB

use follow this and run

```sql
CREATE DATABASE questdb_datasource
WITH
  ENGINE = 'questdb',
  PARAMETERS = {
    "host": "database",
    "port": 8812,
    "database": "sensor",
    "user": "admin",
    "password": "quest"
  };
```

## Anomaly Detection Models

```sql
CREATE ANOMALY DETECTION MODEL anomaly_detection_model
FROM questdb_datasource
    (SELECT * FROM sensors)
PREDICT temperature , humidty
USING
      engine = 'anomaly_detection_engine';
DESCRIBE MODEL mindsdb.unsupervised_ad.model;

SELECT t.class, m.outlier as anomaly
FROM files.anomaly_detection as t
JOIN mindsdb.unsupervised_ad as m;
```


## Time Series Models

```sql
CREATE ML_ENGINE statsforecast
FROM statsforecast;
```
```sql
CREATE MODEL model_name
FROM questdb_datasource
  (SELECT * FROM sensor)
PREDICT temperature,humidity
ORDER BY timestamp
WINDOW 12 -- model looks back at sets of 12 rows each
HORIZON 3 -- model forecasts the next 3 rows
USING
  engine = 'statsforecast',
  model_name = 'model',
  frequency = 'X',
  season_length = 1,
  hierarchy = ['column'];
```
