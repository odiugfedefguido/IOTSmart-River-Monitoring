<!-- Based on: https://svelte.dev/examples/area-chart. -->
<script>
	import { scaleLinear } from 'd3-scale';
    export let dataPoints;

	const yTicks = [0, 20, 40, 60, 80, 100];
	$: xTicks = [0, dataPoints.length-1];
	const padding = { top: 20, right: 15, bottom: 20, left: 25 };

	let width = 1000;
	let height = 600;

    $: minX = 0;
	$: maxX = dataPoints.length-1;

	$: xScale = scaleLinear()
		.domain([minX, maxX])
		.range([padding.left, width - padding.right]);

	$: yScale = scaleLinear()
		.domain([Math.min.apply(null, yTicks), Math.max.apply(null, yTicks)])
		.range([height - padding.bottom, padding.top]);

	$: path = `M${dataPoints.map((p, i) => `${xScale(i)},${yScale(p)}`).join('L')}`;
	$: area = `${path}L${xScale(maxX)},${yScale(0)}L${xScale(minX)},${yScale(0)}Z`;

	function formatMobile(tick) {
		return "'" + tick.toString().slice(-2);
	}
</script>

<div class="chart" bind:clientWidth={width} bind:clientHeight={height}>
	<svg>
		<!-- y axis -->
		<g class="axis y-axis" transform="translate(0, {padding.top})">
			{#each yTicks as tick}
				<g class="tick tick-{tick}" transform="translate(0, {yScale(tick) - padding.bottom})">
					<line x2="100%" />
					<text y="-4">{tick} {tick === 8 ? ' million sq km' : ''}</text>
				</g>
			{/each}
		</g>

		<!-- x axis -->
		<g class="axis x-axis">
			{#each xTicks as tick}
				<g class="tick tick-{tick}" transform="translate({xScale(tick)},{height})">
					<line y1="-{height}" y2="-{padding.bottom}" x1="0" x2="0" />
					<text y="-2">{width > 380 ? tick : formatMobile(tick)}</text>
				</g>
			{/each}
		</g>

		<!-- data -->
		<path class="path-area" d={area} />
		<path class="path-line" d={path} />
	</svg>
</div>

<style>
	.chart,
	h2,
	p {
		max-width: 100vw;
		width: 1000px;
		margin-left: auto;
		margin-right: auto;
	}

	svg {
		position: relative;
		width: 100%;
		height: 600px;
		overflow: visible;
	}

	.tick {
		font-size: 0.725em;
		font-weight: 200;
	}

	.tick line {
		stroke: #888;
		stroke-dasharray: 2;
	}

	.tick text {
		fill: #888;
		text-anchor: start;
	}

	.tick.tick-0 line {
		stroke-dasharray: 0;
	}

	.x-axis .tick text {
		text-anchor: middle;
	}

	.path-line {
		fill: none;
		stroke: rgb(0, 168, 168);
		stroke-linejoin: round;
		stroke-linecap: round;
		stroke-width: 2;
	}

	.path-area {
		fill: rgba(0, 128, 128, 0.2);
	}
</style>
