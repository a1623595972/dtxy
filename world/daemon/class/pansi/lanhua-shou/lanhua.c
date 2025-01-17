#include <ansi.h>

inherit SSERVER;
mapping xue_name = ([
	"xue_name1" : ({ HIR"劳宫穴"NOR,HIR"膻中穴"NOR,HIR"曲池穴"NOR, }),
	"xue_name2" : ({ HIG"关元穴"NOR,HIG"曲骨穴"NOR,HIG"中极穴"NOR, }),
	"xue_name3" : ({ HIY"承浆穴"NOR,HIY"天突穴"NOR,HIY"百会穴"NOR, }),
	"xue_name4" : ({ HIM"幽门穴"NOR,HIM"章门穴"NOR,HIM"大横穴"NOR, }),
	"xue_name5" : ({ HIW"紫宫穴"NOR,HIW"冷渊穴"NOR,HIW"天井穴"NOR, }),
	"xue_name6" : ({ HIC"极泉穴"NOR,HIC"清灵穴"NOR,HIC"至阳穴"NOR, }),
	"xue_name7" : ({ HIB"四白穴"NOR,HIB"大迎穴"NOR,HIB"峡车穴"NOR, }),
	"xue_name8" : ({ WHT"隐白穴"NOR,WHT"太白穴"NOR,WHT"地机穴"NOR, }),
	"xue_name9" : ({ CYN"少冲穴"NOR,CYN"少海穴"NOR,CYN"神门穴"NOR, }),
]);
int perform(object me, object target)
{
        int damage,damage1,ap,dp;
        string msg,xuedao;

        int num,num_hit,i;
        int cd = 10;
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("你没有在战斗。\n");
                
        if( (int)me->query_skill("lanhua-shou", 1) < 150 )
                return notify_fail("你的兰花手不够娴熟。\n");

        if( (int)me->query_skill("jiuyin-xinjing", 1) < 150 )
                return notify_fail("你的九阴心经太低。\n");

        if( (int)me->query("force") < 1000 )
                return notify_fail("你内力太弱。\n");
	 if(!wizardp(me) && me->query("family/family_name")!="盘丝洞")
		return notify_fail("你不是盘丝洞弟子，无法凝气成兰！\n");
	if( me->query("lunhui_zhuanshi") > 4 )
		cd = 6;
	else if( me->query("lunhui_zhuanshi") > 1 )
		cd = 8;
        if( time() - (int)me->query_temp("lanhua_time") < cd )
                 return notify_fail("你无法连续凝气成兰。\n");
        me->set_temp("lanhua_time",time());
        num = (me->query_skill("jiuyin-xinjing", 1) - 100)/50;
        num = num + random(num) + 1;
        ap = me->query("combat_exp")/10000;
        dp =  target->query("combat_exp")/10000;
        damage1 =  me->query_skill("unarmed")/2 + me->query_str() +random(me->query_skill("force")/4);
        if( num > 9 ) num = 9;
        msg = HIW "\n$N轻抬右手，九阴真气慢慢在你指尖汇聚，不一会竟然凝成"+HIY+ chinese_number(num) +HIW"朵光华粲然的"+BLINK+HIB"兰花"+NOR+HIW"。\n"NOR;
	msg = msg + HIC "\n$N微微一笑，指扣轻弹"+BLINK+HIB"兰花"+NOR+HIC"划出美妙的弧线，缓缓飞向$n。\n"NOR;
	msg = msg + RED "\n$n暗暗运气戒备，却也不忍错过这"+BLINK+HIB"兰花"+NOR+RED"胜景。\n"NOR;
	msg = msg + HIC "\n$N打个响指，"+BLINK+HIB"兰花"+NOR+HIC"陡然加速，冲向$n周身要穴。\n"NOR;
	message_vision(msg, me, target);
	xuedao = "";
	for( i = 1 ; i <= num ; i++ )
	{
		if( random(ap) > dp/3 ) 
		{
			num_hit++;
			xuedao = xuedao + xue_name["xue_name" + i][random(3)] + " ";
		}
	}
	if( num_hit > 0 )
	{
		msg = HIR "\n$n虽然戒备有加，却是想不$N控制如此高明，手忙脚乱间被"+BLINK+HIB"兰花"+NOR+HIR"击中了\n"NOR;
		msg = msg + "\n\t\t" + xuedao + "\n\n"NOR;
		message_vision(msg, me, target);
		damage = damage1*num_hit;
		damage = damage - target->query_temp("apply/armor");
		if( damage < damage1 ) damage =  damage1;
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		COMBAT_D->report_status(target);
                me->add("force",-damage/5);
	}
	else
	{
		me->add("force",-100);	
		msg = HIG "\n$n虽然有点手忙脚乱，不过还是躲过了$N所有的攻击。\n"NOR;
		message_vision(msg, me, target);
	}
        return 1;
}
