// by happ@YSZZ

#include <armor.h>

inherit CLOTH;

void create()
{
   set_name("��Ыʥ��", ({ "tianxie shengyi" }) );
   set_weight(3000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "��");
     set("material", "steel");
     set("armor_prop/armor",55);
   }
   set("special_effects", "��");  // emotion
   setup();
}
