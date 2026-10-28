#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// physical port
 typedef struct{
char portName[5]; //configurable portName
 int speed; // speed in bytes
int mode; // full or half duplex
int switchport_mode; // 0 - access port, 1 - trunkport 
int Vlan; // Vlan
 int status; // 0 - administratively down, 1 - administratively enabled,
}port;
// MAC row table
typedef struct{
char port[4];
char MAC[17];
int Vlan;
int type;
}mac_row;
// initialize default port configuration
 void init_port(port *portname, char name[5], int speed);
//check if MAC address exists in the MAC table
int check_ifMACExists(char MAC[17], mac_row *MAC_table);
// create a entry on the MAC table
// identify incoming port and create the entry
void create_MAC_entry(int portNum, mac_row table[], char MAC[17], int Vlan){
//check if the MAC exists on the MAC table
  if(check_ifMACExists(MAC, table) == 0){
  return;
  }
table[portNum].Vlan = Vlan;
strcpy(table[portNum].MAC, MAC);
}

void listen();

void show_MAC_table();

mac_row MAC_table[6];
port port_list[6];

void switch_packet(int portNum, char Sour_MAC[17], char Dest_MAC[17]);

 void main() {
port gigabit_one = {0};
char ports[6][5] = {"G0/0", "G0/1", "F0/1", "F0/2", "F0/3", "F0/4"};

int i ;
for(i = 0; i < 6; i ++){
MAC_table[i] = (mac_row){0};
port_list[i] = (port){0};
strcpy(port_list[i].portName, ports[i]);
  }

for(int i = 0; i < 6; i++)
  strcpy(MAC_table[i].port, ports[i]);

  create_MAC_entry(0, MAC_table, "00:1A:2B:3C:4D:5E", 13);
create_MAC_entry(1, MAC_table, "00:1A:2B:b6:4D:5F", 54);
  
  

  printf("Switch booting up...\n");
  //printf("%s\n", port_list[0].portName);
  sleep(3);
  //show_MAC_table(MAC_table);
  while (1) {
  listen();
  }
}

void show_MAC_table(){
  printf("\n%-50s\n", "MAC Address Table");
  printf("%-5s %-20s %-10s %-10s\n", "Vlan", "MAC Address", "Type", "Port");
  int i = 0;
  for(i = 0; i < 6; i++){
    printf("%-5d %-20s %-10s %-10s\n", MAC_table[i].Vlan, MAC_table[i].MAC, MAC_table[i].type == 0 ? "Dynamic" : "Static", MAC_table[i].port);
  }
  }

// outputs the cli and get command
void listen(){
  char cmd[100]; 
  printf("switch# ");
  scanf(" %[^\n]", cmd);
  if(strcmp(cmd, "show mac_table") == 0){
  show_MAC_table(MAC_table);
  } else if(strcmp(cmd, "exit") == 0){
  exit(0);
  } else if(strcmp(cmd, "switch packet") == 0){
switch_packet(4, "11:1A:2B:3C:4D:5E", "00:1A:22:b6:4D:5F");
  }
  else {
    printf(" \033[1;31m Invalid command \033[0m\n");
  }
}
 void init_port(port *portname, char name[5], int speed){
 strcpy(portname->portName, name);
 portname->speed = speed;
 portname->mode = 1;
 portname->switchport_mode = 1;
 portname->Vlan = 1;
 portname->status = 1;
 }

 int check_ifMACExists(char MAC[50], mac_row *MAC_table){
 for(int i = 0; i < 6; i++){
 if(strcmp(MAC_table[i].MAC, MAC) == 0)
return 0;
 }
 return 1;
}

void switch_packet(int portNum, char Sour_MAC[12], char Dest_MAC[12]){
 create_MAC_entry(portNum, MAC_table, Sour_MAC, 0);
int i = 0;
for(i = 0; i < 6; i++){
  if(strcmp(MAC_table[i].MAC, Dest_MAC) == 0){
      printf("Packet forwarded to port %s\n", MAC_table[i].port);
      return;
    }
  }
  printf("packet flooded to all port except incoming port\n");
}

