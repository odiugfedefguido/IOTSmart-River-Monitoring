<script>
    import Diagram from './Diagram.svelte';
    import '../style.css';
    import { onMount, onDestroy } from "svelte";

    const BACKEND_URL = 'http://localhost:8080/api';

    let controlState = 'AUTOMATIC';
    let valveAngle = 100;
    let valveState = 'NORMAL';
    let dataPoints = [];

    async function fetchData() {
        fetch(BACKEND_URL + '/data')
            .then(response => response.json())
            .then(data => {
                console.debug(data);
                controlState = data.controlState;
                valveState = data.valveState;
                valveAngle = data.valveAngle;
                dataPoints = data.history;
            });
    }

    const interval = setInterval(async () => {
        fetchData();
    }, 500);

    onMount(async () => {
        fetchData();
    });

    onDestroy(() => clearInterval(interval));

    function updateValveAngle () {
        console.log("New valve angle: " + valveAngle);
        fetch(BACKEND_URL + "/data", {
            method: "post",
            headers: {
                'Accept': 'application/json',
                'Content-Type': 'application/json'
            },

            body: JSON.stringify({
                valveAngle: valveAngle
            })
        }).then( (response) => { 
            console.debug(response)
        });
    }
</script>

<section class="section-stats">
    <h1>River Monitoring Dashboard</h1>
    <p>Control: <br/>{ controlState }</p>
    <p>State: <br/>{ valveState }</p>

    <form>
        <label for="valve-input">Valve angle: { valveAngle }</label><br/>
        <input name="valve-input" disabled={ controlState === 'AUTOMATIC' } type="range" min="0" max="180" bind:value={valveAngle} on:change={updateValveAngle} />
    </form>
</section>

<section class="section-diagram">
    <Diagram dataPoints={dataPoints} />
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