// hammer.c

#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("ͭ��", ({"hammer"}));
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����ص�ͭ����������൱��ʵ��\n");
                set("value", 500);
                set("material", "iron");
                set("wield_msg",
"$N�ó�һ��$n��������������Ȼ���������С�\n");
                set("unwield_msg", "$N�������е�$n��\n");
        }

	set("special_effects", "none");  // emotion
        init_hammer(25);
        setup();
}
