// writted by jie
// 2/2001

#include <ansi.h>
#include <combat.h>

inherit SSERVER;

int perform(object me, object target)
{       
        string str,msg="";
        int damage,wound,skill;
	int cd = 6;
        object weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ���ȹ��նɡ���\n");
	if ( time() - me->query_temp("lastchaodu") < cd )
		return notify_fail("��ո�ʹ�����ȹ��նɡ����У�����Ъ����ɡ�\n");

        if(!me->is_fighting())
                return notify_fail("���ȹ��նɡ�ֻ����ս����ʹ�ã�\n");
        
        if(!wizardp(me) && me->query("family/family_name")!="�Ϻ�����ɽ")
                return notify_fail("���Ƿ��ŵ��Ӳ����á��ȹ��նɡ���\n");
        // ����ɱ���ߣ����󲻷�����ʵ�������趨��ɱ������
        if( (int)me->query("bellicosity") > 300 )
        return notify_fail("���ɱ��̫�أ��޷�ʩչ���ž�����\n");
                
        if (me->query_skill_mapped("force")!="lotusforce")
                return notify_fail("���ȹ��նɡ���������̨�ķ�Ϊ���ӣ�\n");
                
        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 300 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("lotusforce", 1) < 80)
                return notify_fail("�����̨�ķ���Ϊ��������ʹ����һ�л������ѣ�\n");
        if((int)me->query_skill("jienan-zhi", 1) < 80)
                return notify_fail("��Ľ���ָ��Ϊ��������ʹ����һ�л������ѣ�\n");
	me->add("force", -100);
	me->set_temp("lastchaodu",time());
        message_vision(HIY"$N������������ջ�������⣬��ת�������ھ��С��ȹ��նɡ�����$n��������������\n"NOR,me,target);
        me->set("ciguangpudu", 6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("ciguangpudu", 7);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("ciguangpudu", 8);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("ciguangpudu", 9);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->delete("ciguangpudu");
        //me->start_busy(2+random(1));
	message_vision(RED"\n$N"+NOR+RED+"��ʽһ�䣬���������ڱ��������������\n"NOR,me,target);
	message_vision(HIB"\n\n\n            ��"+HIG+"���ѵ�"+HIB+"��\n\n\n"NOR,me,target);
	message_vision(RED"һ��ɭ�������ε�������$n��\n"NOR,me,target);
	skill = me->query_skill("unarmed");
	if( random(skill + target->query_skill("unarmed") / 2) > target->query_skill("unarmed", 1) / 2 )
	{
		skill = me->query_skill("unarmed");
        	damage = random(skill / 2) + skill * 2;
        	damage -= target->query_temp("apply/armor");
           	if(damage < skill) damage = skill;           
           	target->receive_wound("kee", 1 + random(damage/2), me);
            	target->receive_damage("kee", damage, me);
            	message_vision(HIR"����һ���Ѳ����죬$n"+HIR+"��������һ�������Ѫ�ۣ�\n"NOR,me,target);
             	COMBAT_D->report_status(target);
        }
        else
        {
        	message_vision(HIG"ֻ��$N"+HIG+"�Ǳ��Ĵ��Ƶ��¶��˹�����\n"NOR,target);
        }
        message_vision(HIY "\n$N������Ź�������ڿ��ϣ����ϣ������ѹ��������������\n"NOR, me, target);
        if( random(me->query_skill("buddhism",1)) > random(target->query_skill("spells",1)/4) )
        {
                message_vision(HIR "\n$n��$N�ķ𷨸л������ڵ��Ѿ��������Լ�����ս��֮�У�\n\n" NOR, me,target);
                damage = me->query_skill("spells");
                damage = damage + random(damage/3);
                target->receive_damage("sen",damage,me);
                target->receive_wound("sen",damage,me);
                COMBAT_D->report_sen_status(target);
        }
        else
                message_vision(HIC "\n$n��е����������죬�����㣡\n\n" NOR, me,target);
        message_vision(HIW"$N�����������ӷ𣡡����ȹ��նɡ��ù���ϣ����ϵ����Ľ��������ȥ.\n"NOR,me,target);
        message_vision(msg,me,target);
        if ( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
        {
        	str=target->name()+HIM"��"+me->name()+"��"+NOR+HIC"���ȹ��նɡ�"+NOR+HIM"�ɻ����ĸ���Ը���˻�Ȫ���ٶ��ֻء�";
    		message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
        me->add("kee", -100);
        me->add("sen",-100);
        return 1;
}