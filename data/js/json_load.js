var running = false;
var nixie_time,
    ip_addr,
    mode_wifi,
    free_heap;

function run_index() {
  if (!running)
  {
    running = true;
  }
}

setInterval(function getData() {
  if (!running) return;
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var res = JSON.parse(xhttp.responseText);
      display.setValue(res.nixie_time);
      document.getElementById("free_heap").textContent = "Free Heap: " + res.free_heap;
    }
  };
  xhttp.open("GET", "/json", true);
  xhttp.send();
}, 1000);