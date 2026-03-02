
const char Switch_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Switch Buttons Example</title>
  <!-- Bootstrap CSS -->
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body class="bg-light">

<div class="container py-5">
  <h2 class="mb-4">Switch Buttons (AJAX POST led & state)</h2>

  <!-- Switch 1 -->
  <div class="form-check form-switch mb-3">
    <input class="form-check-input" type="checkbox" id="switch1" onchange="submitSwitch(1)">
    <label class="form-check-label me-3" for="switch1">Switch 1</label>
    <span id="status1" class="fw-bold text-secondary">OFF</span>
  </div>

  <!-- Switch 2 -->
  <div class="form-check form-switch mb-3">
    <input class="form-check-input" type="checkbox" id="switch2" onchange="submitSwitch(2)">
    <label class="form-check-label me-3" for="switch2">Switch 2</label>
    <span id="status2" class="fw-bold text-secondary">OFF</span>
  </div>

  <!-- Switch 3 -->
  <div class="form-check form-switch mb-3">
    <input class="form-check-input" type="checkbox" id="switch3" onchange="submitSwitch(3)">
    <label class="form-check-label me-3" for="switch3">Switch 3</label>
    <span id="status3" class="fw-bold text-secondary">OFF</span>
  </div>

  <!-- Switch 4 -->
  <div class="form-check form-switch mb-3">
    <input class="form-check-input" type="checkbox" id="switch4" onchange="submitSwitch(4)">
    <label class="form-check-label me-3" for="switch4">Switch 4</label>
    <span id="status4" class="fw-bold text-secondary">OFF</span>
  </div>

  <!-- Switch 5 -->
  <div class="form-check form-switch mb-3">
    <input class="form-check-input" type="checkbox" id="switch5" onchange="submitSwitch(5)">
    <label class="form-check-label me-3" for="switch5">Switch 5</label>
    <span id="status5" class="fw-bold text-secondary">OFF</span>
  </div>

  <!-- Server Response -->
  <div class="mt-4">
    <h5>Received Data:</h5>
    <p id="serverResponse" class="fw-bold text-primary">No data yet</p>
  </div>
</div>

<!-- JavaScript -->
<script>
  function updateStatus(num) {
    const sw = document.getElementById("switch" + num);
    const status = document.getElementById("status" + num);
    if (sw.checked) {
      status.textContent = "ON";
      status.classList.remove("text-secondary");
      status.classList.add("text-success");
      return "on";
    } else {
      status.textContent = "OFF";
      status.classList.remove("text-success");
      status.classList.add("text-secondary");
      return "off";
    }
  }

  function submitSwitch(num) {
    const state = updateStatus(num);

    fetch("", {
      method: "POST",
      headers: {
        "Content-Type": "application/x-www-form-urlencoded"
      },
      body: `led=${num}&state=${state}`
    })
    .then(response => response.text())
    .then(data => {
      // Just show the raw string returned by server
      document.getElementById("serverResponse").textContent = data;
    })
    .catch(err => {
      console.error("Error:", err);
    });
  }
</script>

</body>
</html>

)=====";