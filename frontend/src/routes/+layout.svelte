<script lang="ts">
	import '../app.css';
	import 'carbon-components-svelte/css/all.css';
	let { children } = $props();
	import {
		Header,
		HeaderNav,
		HeaderNavItem,
		SkipToContent,
		Content,
		Grid,
		Row,
		Column,
		SideNav,
		SideNavItems,
		SideNavMenu,
		SideNavMenuItem,
		SideNavLink
	} from 'carbon-components-svelte';
	function isDaytime(date: Date = new Date()): boolean {
		const hours = date.getHours();
		// Define daytime as between sunrise (e.g., 6 AM) and sunset (e.g., 6 PM).  Adjust as needed.
		return hours >= 6 && hours < 18;
	}
	$effect(() => {
		// "white" | "g10" | "g80" |  | "g100"
		/*let theme =
			localStorage.getItem('theme') != null && localStorage.getItem('theme') != ''
				? String(localStorage.getItem('theme'))
				: 'g100';*/
		let theme = isDaytime(new Date()) ? 'g90' : 'g100';
		document.documentElement.setAttribute('theme', theme);

		//if (!(localStorage.getItem('theme') != null && localStorage.getItem('theme') != '')) {
			localStorage.setItem('theme', theme);
		//}
	});

	let isSideNavOpen = $state(false);
</script>

<Header
	persistentHamburgerMenu={true}
	company="IBM"
	platformName="Carbon Svelte"
	bind:isSideNavOpen
>
	<svelte:fragment slot="skip-to-content">
		<SkipToContent />
	</svelte:fragment>
	<HeaderNav>
		<HeaderNavItem href="/" text="Docs" />
		<HeaderNavItem href="/" text="About" />
	</HeaderNav>
</Header>
<SideNav bind:isOpen={isSideNavOpen}>
	<SideNavItems>
		<SideNavLink href="/" text="Docs" />
		<SideNavLink href="/" text="About" />
	</SideNavItems>
</SideNav>

<Content>
	<Grid>
		<Row>
			<Column>
				{@render children()}
			</Column>
		</Row>
	</Grid>
</Content>
