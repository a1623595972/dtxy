#include <weapon.h>

inherit STICK;

void create()
{
        set_name("ɱ�����", ({"shawei bang", "bang"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200);
                set("material", "wood");
             }
	set("special_effects", "none");  // emotion
        init_stick(25);
        setup();
}

