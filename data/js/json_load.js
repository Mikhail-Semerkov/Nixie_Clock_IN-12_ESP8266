var reloadPeriod = 1000;
var running = false;
var setting_load = false;

var nixie_time_js;
var nixie_time;

function run_index() {
  if (!running)
  {
    running = true;
    loadValues();
  }
}

function loadValues() {
  if (!running) return;
  var xh = new XMLHttpRequest();
  xh.onreadystatechange = function () {
    if (xh.readyState == 4) {
      if (xh.status == 200) {
        var res = JSON.parse(xh.responseText);
        nixie_time = res.nixie_time_js;
      
        if (running) setTimeout(loadValues, reloadPeriod);
      }
      else running = false;
    }
  };
  xh.open("GET", "/json", true);
  xh.send();
}


var display = new SegmentDisplay("display");
  display.pattern         = "######";
  display.displayAngle    = 0;
  display.digitHeight     = 50;
  display.digitWidth      = 28;
  display.digitDistance   = 6.4;
  display.segmentWidth    = 4.5;
  display.segmentDistance = 1.1;
  display.segmentCount    = 14;
  display.cornerType      = 0;
  display.colorOn = "#EFEFEF";
  display.colorOff = "#232746";
  display.draw();
      
      animate();

      function animate() {
        
        display.setValue(nixie_time);
        window.setTimeout("animate()", 100);
      }



  

