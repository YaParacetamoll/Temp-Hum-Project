export interface Pretty{
    group:string;
    value:string | number;
    temp:string;
    hum:string;
    ts:Date | string;
}

export interface ValueIn{
    flag: string, 
    id: string, 
    T: number, 
    H: number
}
export default function valMqttToPrettyFormat(value:ValueIn):Pretty[]{
    value.H = parseFloat(value.H +"")
    value.T = parseFloat(value.T +"")
    //console.log(value)
    return [
        {
            group: "Temp-"+value.id,
            value: value.T,
            ts: new Date(Date.now()).toLocaleTimeString(),
            temp: value.T+"°C",
            hum:  value.H+"%"
        },
        {
            group: "Hum-"+value.id,
            value: value.T,
            ts: new Date(Date.now()).toLocaleTimeString(),
            temp: value.T+"°C",
            hum:  value.H+"%"
        }
    ]
}
