// copperjian.c
// created 5-30-97 pickle

#include <weapon.h>
#include <ansi.h>

inherit MACE;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
  set_name("�", ({"mace"}));
  set_weight(5000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("value", 2000);
    set("material", "copper");
    set("long", "һ����ע��ħ����ﵣ�");
    set("wield_msg", "$N����һ��$n���ڵ���ײ�������ǡ�\n");
    set("unwield_msg", "$NĨ��Ĩ$n�ϵ��⣬��������������\n");
  }
  
  init_mace(25);
  setup();
}
