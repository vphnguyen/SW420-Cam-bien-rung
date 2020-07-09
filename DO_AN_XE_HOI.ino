
const byte cambienrung = 2; //chan d2 hoac d3 
const byte coibao = 5;
const byte khoa = 6;
bool baodong=false;
#define thoi_gian_chong_nhieu 1000
#define thoi_gian_de_bat_bao_dong 800

static unsigned long rung_lan_dau=0;
static unsigned long rung_lan_cuoi=0;
static unsigned long rung_truoc_lan_cuoi=0;

bool them(unsigned long gia_tri){
  if(rung_lan_dau==0){
    rung_lan_dau=gia_tri;
    rung_truoc_lan_cuoi=gia_tri;
    rung_lan_cuoi=gia_tri;
    return true;
  }
  if(rung_lan_cuoi==0){
    rung_lan_cuoi=gia_tri;
    rung_truoc_lan_cuoi=gia_tri;
    return true;
  }
  else{
    if((gia_tri - rung_truoc_lan_cuoi)  >= thoi_gian_chong_nhieu){
      
         Serial.print("\nKET THUC CHU TRINH");
          rung_lan_dau=0;
          rung_truoc_lan_cuoi=0;
          rung_lan_cuoi=0;
          return true;
    }
    rung_truoc_lan_cuoi=rung_lan_cuoi;
    rung_lan_cuoi=gia_tri;
    return true;
  }
}
bool kiem_tra(){
  unsigned long thoi_gian_keo_dai= rung_lan_cuoi-rung_lan_dau; 
  
  Serial.print("\nKET QUA KIEM TRA:");
  
  Serial.print(thoi_gian_keo_dai);
  if( thoi_gian_keo_dai >= thoi_gian_de_bat_bao_dong)
    return true;
  else 
    return false;
}
void bao_dong(){
  baodong=true;
  Serial.print("\n\t\t\tBAO DONG !!!\n");
  digitalWrite(coibao,HIGH);
  digitalWrite(khoa , HIGH);
}
// ------------------------------------------------------------------
// INTERRUPT     NGAT     NGAT      NGAT      NGAT
// ------------------------------------------------------------------
void nhan_tin_hieu_rung(){
  if(baodong==false){
    them(millis());
    if(kiem_tra())bao_dong();
  }
}
void setup() {
  // put your setup code here, to run once:
  baodong=false;
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(cambienrung), nhan_tin_hieu_rung, HIGH);
  pinMode(coibao, OUTPUT);
  pinMode(khoa, OUTPUT);
  //TAT COI VA MO KHOA KHI KHOI DONG MACH
  digitalWrite(coibao , LOW);
  digitalWrite(khoa,LOW) ;
}


void loop() {
  // put your main code here, to run repeatedly:

}
