// blade.c

#include <weapon.h>

inherit BLADE;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
	set_name("��", ({"blade" }) );
	set_weight(4000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 500);
		set("material", "iron");
		set("long", "����һ�Ѳ�Ѱ���ĵ�����������Լ�����߽��أ�");
		set("wield_msg", "$N���һ�����λε�$n�������С�\n");
		set("unequip_msg", "$N�����е�$n��������ĵ��ʡ�\n");
	}
	init_blade(25);
	setup();
}