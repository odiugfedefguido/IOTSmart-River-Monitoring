<script>
    import Diagram from './Diagram.svelte';
    import '../style.css';

	let isAutomatic = true;
    let valveLevel = 100;
    let state = 'NORMAL';

    function updateValveLevel () {
        console.log("Valve level: " + valveLevel);
        // TODO: Communicate new valve level to backend.
    }
</script>

<section class="section-stats">
    <h1>River Monitoring Dashboard</h1>
    <p>Control: <br/>{ isAutomatic == true ? 'AUTOMATIC' : 'MANUAL' }</p>
    <p>State: <br/>{ state }</p>

    <form>
        <label for="valve-input">Valve level: { valveLevel }</label><br/>
        <input name="valve-input" disabled={isAutomatic} type="range" min="0" max="180" bind:value={valveLevel} on:change={updateValveLevel} />
    </form>
</section>

<section class="section-diagram">
    <Diagram />
</section>

<style>
h1 {
    font-size: 2rem;
}

.section-stats {
    display: flex;
    align-items: start;
    gap: 2rem;
}
</style>