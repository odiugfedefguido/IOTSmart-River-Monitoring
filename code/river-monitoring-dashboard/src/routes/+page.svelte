<script>
    import Diagram from './Diagram.svelte';
    import '../style.css';
    import { onMount, onDestroy } from "svelte";

    const BACKEND_URL = 'http://localhost:8080/api';

    // initial data to be displayed
    let controlState = 'AUTOMATIC';
    let valveAngle = 100;
    let valveState = 'NORMAL';
    let dataPoints = [];

    // function to retrieve data from the backend
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

    // fetch data every 500 ms as well as on pageload
    const interval = setInterval(async () => fetchData(), 500);
    onMount(async () => fetchData());
    onDestroy(() => clearInterval(interval));

    // sending new valve angle to the server in DASHBOARD mode
    function updateValveAngle () {
        console.log("New valve angle: " + valveAngle);
        fetch(BACKEND_URL + "/data", {
            method: "post",
            headers: {
                'Accept': 'application/json',
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ valveAngle: valveAngle })
        }).then( (response) => { 
            console.debug(response)
        });
    }

    // switch between AUTOMATIC and DASHBOARD mode
    function switchMode () {
        console.log("Attempting to switch mode.");
        fetch(BACKEND_URL + "/mode", {
            method: "post",
            headers: {
                'Accept': 'application/json',
                'Content-Type': 'application/json'
            }
        }).then( (response) => { 
            console.debug(response)
        });
    }
</script>

<section class="section-stats">
    <h1>River Monitoring Dashboard</h1>

    <p> 
        Control: <br/>
        <button class="status-value" disabled={controlState === 'MANUAL'} on:click={switchMode}>
            { controlState }
        </button>
    </p>

    <p>
        State: <br/>
        <span class="status-value">{ valveState }</span>
    </p>

    <form>
        <label for="valve-input">Valve angle: { valveAngle }</label><br/>
        <input name="valve-input" disabled={ controlState === 'AUTOMATIC' } type="range" min="0" max="180" bind:value={valveAngle} on:change={updateValveAngle} />
    </form>
</section>

<section class="section-diagram">
    <Diagram dataPoints={dataPoints} />
</section>