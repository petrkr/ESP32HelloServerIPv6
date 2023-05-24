# ESP32 Hello server IPv6

Demo with IPv6 socket on ESP32

Optionaly it needs update WiFiSTA in SDK to support print of global IPv6

WiFiSTA.cpp
```
/**
 * Get the station interface IPv6 address.
 * @return IPv6Address
 */
IPv6Address WiFiSTAClass::globalIPv6()
{
	esp_ip6_addr_t addr;
    if(WiFiGenericClass::getMode() == WIFI_MODE_NULL){
        return IPv6Address();
    }
    if(esp_netif_get_ip6_global(get_esp_interface_netif(ESP_IF_WIFI_STA), &addr)) {
        return IPv6Address();
    }
    return IPv6Address(addr.addr);
}
```

WiFiSTA.h
```
    IPv6Address globalIPv6();
```
