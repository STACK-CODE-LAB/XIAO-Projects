let globalData = [];

async function fetchData() {
  try {
    const res = await fetch('/data');
    const data = await res.json();

    globalData = data;
    document.getElementById("status").innerText = "Connected";

  } catch {
    document.getElementById("status").innerText = "Disconnected";
  }
}

function getMonitorData(id) {
  return globalData.filter(d => d.monitor_id == id);
}

function renderMonitor(id) {
  const data = getMonitorData(id);

  const panel = document.getElementById("panel-content");
  const title = document.getElementById("panel-title");

  title.innerText = "Monitor " + id;

  if (data.length === 0) {
    panel.innerHTML = "No data";
    return;
  }

  let html = "<table border='1'>";
  html += "<tr><th>Node</th><th>Temp</th><th>Act</th></tr>";

  data.slice(-10).forEach(d => {
    html += `
      <tr>
        <td>${d.node_id}</td>
        <td>${d.temp}</td>
        <td>${d.activity}</td>
      </tr>
    `;
  });

  html += "</table>";

  panel.innerHTML = html;
}

document.querySelectorAll(".marker").forEach(marker => {
  marker.onclick = () => {
    const id = marker.getAttribute("data-id");
    renderMonitor(id);
  };
});

setInterval(fetchData, 3000);
fetchData();