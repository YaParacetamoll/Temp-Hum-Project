export interface Pretty{
    group:string;
    value:string | number;
    ts:Date | string;
}

export interface ValueIn{
    flag: string, 
    id: string, 
    T: number, 
    H: number
}
export default function valMqttToPrettyFormat(value:ValueIn,now:string):Pretty[]{
    value.H = parseFloat(value.H +"")
    value.T = parseFloat(value.T +"")

    //console.log(value)
    return [
        {
            group: "Temp-"+value.id,
            value: value.T,
            ts: new Date(Date.now()).toLocaleTimeString()
        },
        {
            group: "Hum-"+value.id,
            value: value.T,
            ts: new Date(Date.now()).toLocaleTimeString()
        }
    ]
}
