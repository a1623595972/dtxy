// blade.c

#include <weapon.h>

inherit BLADE;

void create()
{
	set_name("�˵�", ({ "cai dao", "dao", "knife" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 100);
		set("material", "iron");
		set("long", "����һѰ���Ĳ˵���������Լ�����߽��ء�\n");
		set("wield_msg", "$N���һ��Ѫ���ܵ�$n�������С�\n");
		set("unequip_msg", "$N���½����е�$n��\n");
	}
	set("special_effects", "none");  // emotion
	init_blade(10);
	setup();
}