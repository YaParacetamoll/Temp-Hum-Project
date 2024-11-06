<script>
	import { Tile, Content } from 'carbon-components-svelte';
	import { StackedAreaChart } from '@carbon/charts-svelte';
	import { truncate } from 'carbon-components-svelte';
	import '@carbon/charts-svelte/styles.css';

	import options from '$lib/chartOption';
	import data from '$lib/mockData';
	import { ImageLoader } from 'carbon-components-svelte';

	import { writable } from 'svelte/store';
	import { Asleep } from '@carbon/icons-react';

	const opt = writable(options);
	$effect(() => {
		//opt.theme = "white"
		opt.update((o) => {
			o.theme = localStorage.getItem('theme') ?? 'g100';
			return o;
		});
	});
</script>
<svelte:head>
	<title>About | TempHumProject</title>
</svelte:head>
<Content>
	<div class="grid grid-cols-1 gap-5 lg:grid-cols-3">
		<div class="relative flex justify-center lg:col-span-3">
			<img alt="bn" src="/banner.jpeg" class="h-32 w-full object-cover blur-[0.6px] brightness-50" />

			<h1  class="absolute top-0 p-2" use:truncate >TempHum Project</h1>
		</div>
		<Tile class="lg:col-span-3">
			<h3 use:truncate >ภาพรวมของ Project</h3>
			<p use:truncate >
				โครงการนี้มุ่งเน้นการใช้เทคโนโลยี LoRa (Long Range) ในการเก็บข้อมูลจากแหล่งต่าง ๆ
				เพื่อนำมาประมวลผลอุณหภูมิ และความชื้น
				เป้าหมายหลักคือการสร้างระบบที่มีความเชื่อถือได้และใช้พลังงานต่ำสำหรับการเก็บข้อมูลและการส่งข้อมูลอุณหภูมิในระยะทางไกล
				โดยการใช้เทคโนโลยี LoRa ที่สามารถสื่อสารได้ในระยะไกล
				ทำให้สามารถเก็บข้อมูลจากหลายสถานที่ได้อย่างมีประสิทธิภาพ
			</p>
		</Tile>

		<!-- Section 2: LoRa Technology -->
		<Tile class="lg:col-span-3">
			<h3 use:truncate >เทคโนโลยี LoRa</h3>
			<p use:truncate>
				LoRa เป็นโปรโตคอลไร้สายที่ออกแบบมาสำหรับการสื่อสารในระยะไกลและใช้พลังงานต่ำ ในโครงการนี้
				เราใช้เซ็นเซอร์ LoRa เพื่อวัดอุณหภูมิและส่งข้อมูลกลับมายังระบบกลาง
				ซึ่งระบบนี้จะช่วยในการตรวจสอบและบันทึกข้อมูลอุณหภูมิในพื้นที่ต่าง ๆ
				อย่างต่อเนื่องโดยไม่ต้องเปลี่ยนแบตเตอรี่บ่อยหรือใช้ข้อมูลจำนวนมาก
			</p>
		</Tile>

		<!-- Section 3: Data Processing -->
		<Tile class="lg:col-span-3">
			<h3 use:truncate >การประมวลผลข้อมูล</h3>
			<p use:truncate>
				ข้อมูลที่เก็บได้จากเซ็นเซอร์ LoRa จะถูกนำมาประมวลผลและวิเคราะห์ในแบบเรียลไทม์
				โดยข้อมูลอุณหภูมิจากแหล่งต่าง ๆ
				จะถูกรวมเข้าด้วยกันและแสดงผลบนแดชบอร์ดเพื่อให้ผู้ใช้สามารถดูผลลัพธ์และแนวโน้มของอุณหภูมิได้อย่างง่ายดาย
			</p>
		</Tile>

		<!-- Section 4: Temperature Monitoring -->
		<Tile class="lg:col-span-3">
			<h3 use:truncate>การติดตามอุณหภูมิ</h3>
			<p use:truncate>
				ระบบของเราติดตามการอ่านอุณหภูมิอย่างต่อเนื่องและให้ข้อมูลอัปเดตตามช่วงเวลาที่กำหนด
			</p>
		</Tile>
        <Tile class="lg:col-span-3">
			<h3 class="mb-2">สมาชิกกลุ่ม</h3>
			<p>65070195 รตา อุณหะ</p><br>
            <p>65070203 วรดา สาระคนธ์</p><br>
            <p>65070242 สุภัศชัย โพธิชัย</p>
		</Tile>
	</div>
</Content>
