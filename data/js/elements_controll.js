var request = new XMLHttpRequest();

var settings_mode_wifi;
var settings_mode_ap = document.getElementById("settings_mode_ap");
var settings_mode_sta = document.getElementById("settings_mode_sta");
var radio_button_sta = document.getElementById("radio_sta");
var radio_button_ap = document.getElementById("radio_ap");
var label_ip_addr = document.getElementById("label_ip_addr");

var dhcp_mode = document.getElementById("dhcp_mode");

function handleChange(src) {
  if (src.value == "WIFI_STA") {
    settings_mode_wifi = "WIFI_STA";
    settings_mode_sta.style = "";
    settings_mode_ap.style = "display:none";
  } else {
    settings_mode_wifi = "WIFI_AP";
    settings_mode_sta.style = "display:none";
    settings_mode_ap.style = "";
  }
}

function handleCheckBox(src) {
  if (src.checked) {
    dhcp_mode.style = "";
    settings_dhcp.value = 1;
  } else {
    dhcp_mode.style = "display:none";
    settings_dhcp.value = 0;
  }
}

//Reboot
function button_default_reset() {
  console.log("Default Setting");
  request.open("GET", "/default_settings_esp_set", true);
  request.send();
}


function all_save_config() {
  var GET_Server =
    "save_web_config_set?" +
    "mode_wifi=" +
    settings_mode_wifi +
    "&" +
    "wifi_ssid=" +
    settings_wifi_ssid.value +
    "&" +
    "wifi_pass=" +
    settings_wifi_pass.value +
    "&" +
    "port_tcp=" +
    settings_port_tcp.value +
    "&" +
    "mode_serial=" +
    settings_mode_serial.value +
    "&" +
    "serial_baund=" +
    settings_serial_baund.value +
    "&" +
    "dhcp=" +
    settings_dhcp.value +
    "&" +
    "static_ip=" +
    settings_static_ip.value +
    "&" +
    "static_mask=" +
    settings_static_mask.value +
    "&" +
    "static_gataway=" +
    settings_static_gataway.value;

  request.open("GET", GET_Server, true);
  request.send();
}

function reboot_esp() {
  console.log("Reboot ESP32");
  request.open("GET", "/reboot_esp_set", true);
  request.send();

  if ((settings_static_ip.value != "") & (settings_dhcp.value == 1)) {

        let delay = 7000;

    let timerId = setTimeout(function request() {
      setTimeout(() => {
        document.location.href = "http://" + settings_static_ip.value;
      }, 5000);

      timerId = setTimeout(request, delay);
    }, delay);
    
  }

  if (settings_mode_wifi == "WIFI_AP") {
    let delay = 7000;

    let timerId = setTimeout(function request() {
      setTimeout(() => {
        document.location.href = "http://192.168.1.1";
      }, 5000);

      timerId = setTimeout(request, delay);
    }, delay);
  }
}

function home_click() {
  document.location.href = "http://" + window.location.hostname;
}


function terminal_controll_page()
{

  document.location.href = "http://" + window.location.hostname + "/terminal.htm";

}


var Color_Front = document.getElementById("select_color_ws2812");

Color_Front.addEventListener('change', () => {
    Color_Front.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          Color_Front.innerHTML = this.responseText;
        }
    };


    request.open("GET", "select_color_ws2812?color_ws2812=" + Color_Front.value, true);
    request.send();
    //console.log("Select Color Front: " + Color_Front.value.slice(1));
    console.log("COLOR Value - " + Color_Front.value);

});



function HEXtoRGB(hex) {
    hex = hex.replace(/#/g, '');
    if (hex.length === 3) {
        hex = hex.split('').map(function (hex) {
            return hex + hex;
        }).join('');
    }
    // validate hex format
    var result = /^([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})[\da-z]{0,0}$/i.exec(hex);
    if (result) {
        var red = parseInt(result[1], 16);
        var green = parseInt(result[2], 16);
        var blue = parseInt(result[3], 16);

        return [red, green, blue];
    } else {
        // invalid color
        return null;
    }
}


var Color_RGB_WS2812 = document.getElementById("color_led_front");

Color_RGB_WS2812.addEventListener('change', () => {
    Color_RGB_WS2812.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            Color_RGB_WS2812.innerHTML = this.responseText;
        }
    };

    var RGB = HEXtoRGB(Color_RGB_WS2812.value) + ",";
    request.open("GET", "set_rgb_color?rgb_color=" + RGB, true);
    request.send();
    //console.log("Select Color Front: " + Color_Front.value.slice(1));
    console.log("COLOR Value - " + Color_RGB_WS2812.value);

});



