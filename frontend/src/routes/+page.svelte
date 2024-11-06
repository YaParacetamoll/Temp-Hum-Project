<script>
	import { Tile } from 'carbon-components-svelte';
	import { StackedAreaChart } from '@carbon/charts-svelte';
	import { truncate } from 'carbon-components-svelte';
	import '@carbon/charts-svelte/styles.css';
	import options from '$lib/chartOption';
	import data from '$lib/mockData';
	import mqtt from "mqtt";
	import  valMqttToPrettyFormat from "$lib/valMqttToPrettyFormat";
	

	import { writable } from 'svelte/store';

	const opt = writable(options);
	const val = writable([])
	$effect(() => {
		//opt.theme = "white"
		opt.update((o) => {
			o.theme = localStorage.getItem('theme') ?? 'g100';
			return o;
		});

		let client = mqtt.connect('wss://phycom.it.kmitl.ac.th/mqtt',{port:8884,reconnectPeriod:5000});
		client.on('connect', () => {
			client.subscribe('temp-hum-pj/send', (err) => {
			});
		});

		client.on('message', (topic, message) => {
			// message is Buffer
			let tempJson = JSON.parse(message.toString())
			//console.log(valMqttToPrettyFormat(tempJson))
			val.update(
				(v) => [...v, ...valMqttToPrettyFormat(tempJson,v)]
			)
			
			//val.update((v) => [...v, ...valMqttToPrettyFormat(tempJson)]);
		});
	});
</script>

<svelte:head>
	<title>TempHumProject</title>
</svelte:head>
<div class="grid grid-cols-1 gap-5 lg:grid-cols-3">
	<div class="relative lg:col-span-3">
		<img alt="bn" src="/banner.jpeg" class="h-32 w-full object-cover blur-[0.6px]" />

		<h1 class="absolute top-0 p-2">Tempmy</h1>
	</div>

	<Tile class="lg:col-span-3">
		<h3 use:truncate>Analytics</h3>

		<div use:truncate>
			<StackedAreaChart data={$val} options={$opt} style="padding:2rem;" />
		</div>
	</Tile>

	<Tile>
		<h3 use:truncate>Day/Night</h3>
		<div use:truncate>
			<p class="mt-5 text-right text-6xl">Day</p>
		</div>
	</Tile>

	<Tile>
		<h3 use:truncate>Temperature</h3>
		<div use:truncate>
			<p class="mt-5 text-right text-6xl">{[...$val].pop()?.temp}</p>
		</div>
	</Tile>
	<Tile>
		<h3 use:truncate>Hum</h3>
		<div use:truncate>
			<p class="mt-5 text-right text-6xl">{[...$val].pop()?.hum}</p>
		</div>
	</Tile>

	<div class="grid grid-cols-1 gap-1 lg:col-span-3 lg:grid-cols-7">
		<Tile class="lg:col-span-7">
			<h3 use:truncate>7 prev Day</h3>
		</Tile>
		{#each ['Sun', 'Mon', 'Thu', 'Wen', 'Thur', 'Fri', 'Sat'] as d}
			<Tile>
				{d}
			</Tile>
		{/each}
	</div>
</div>
