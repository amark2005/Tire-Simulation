#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;

struct Tire{
  float pressure;
  float p0;
  float temp;
  float t0;
  float wear;
  string grip;
  float slip;
  float throttle;
  float speed;
  float Ticks;
  Tire(int ticks){
    Ticks=ticks;
    wear=0;
  }
  void update() {
    for(int i=0;i<Ticks;i++){
    slipupdate();
    heatupdate();
    pressure_update();
    }
    grip_update();
    wearupdate();
    //display();
  }
  void display(){
    cout<<"\n";
  cout<<"***************************\n";
  cout<<"\tTire Telemetry\n";
  cout<<"***************************\n";
  cout<<"Tire Pressure: "<<pressure<<"psi\n";
  cout<<"Temperature: "<<temp-273.1<<"C\n";
  cout<<"Tire Grip: "<<grip<<"\n";
  cout<<"Slip: "<<slip<<"\n";
  cout<<"Wear: "<<wear<<"\n";
  }
  void wearupdate(){
    wear+=slip*temp*0.0002;
  }
  void heatupdate(){
    float load_heat=(speed/200.0)*50.0f;
    float slip_heat=slip*throttle*150.0f;
    float heat=311.15f+slip_heat+load_heat;
    temp+=(heat-temp)*0.1f;
  }
  void slipupdate(){
    slip=throttle-(speed/200.0);
    if(slip<0)slip=0;
    else if (slip>1)slip=1;
  }
  void pressure_update(){
    pressure=p0*(temp/t0);
  }
  float CtoK(float c){
    return c+273.15;
  }
  void getdata(){
  cout<<"Initial Tire Pressure: ";
  cin>>pressure;
  p0=pressure;
  cout<<"The Initial Tire Temperature(C): ";
  cin>>temp;
  temp=CtoK(temp);
  t0=temp;
  cout<<"Enter Throttle(0-1.0): ";
  cin>>throttle;
  cout<<"Enter the speed(km/h): ";
  cin>>speed;
  }
  void grip_update() {
    if (temp < 328.15)
      grip = "Cold";
    else if (temp < 383.15f)
      grip = "Optimal";
    else
      grip = "OverHeating";
  }
  float find_initial_psi(float targetpsi){
    float lowpsi=20,highpsi=targetpsi;
    for(int i=0;i<50;i++){
      float mid=(highpsi+lowpsi)/2.0f;
      pressure=p0=mid;
      temp=t0;
      update();
      if(pressure<targetpsi)lowpsi=mid;
      else highpsi=mid;
    }
    return (lowpsi+highpsi)/2.0f;
  }
};


int main(){
  float perfectpsi;
  int ticks;
  cout<<"***************************\n";
  cout<<"\tTire Anatomy\n";
  cout<<"***************************\n";
  cout<<"Ticks: ";
  cin>>ticks;
  Tire mazda(ticks);
  mazda.getdata();
  mazda.update();
  mazda.display();
  cout<<"***************************\n";
  cout<<"Perfect Pressure\n";
  cout<<"***************************\n";
  cout<<"Enter the Tire's Recommended psi: ";
  cin>>perfectpsi;
  cout<<"The Suggested Initial Pressure(psi): "<<mazda.find_initial_psi(perfectpsi)<<"\n";

  

  


  
}