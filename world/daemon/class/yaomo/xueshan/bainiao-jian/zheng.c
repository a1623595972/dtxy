//zheng.c kugu 2006.9.15
//xs busy pfm ����һ��
#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap,dp;

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||	!me->is_fighting(target)
        ||      target==me)
           return notify_fail("��Ҫ����˭��\n");
        if( me->query("family/family_name")!="��ѩɽ" )
          	return notify_fail("[��������]ֻ��ѩɽ���Ӳſ����ã�\n");
        if( me->query("force") < 1200 )
		return notify_fail("���������㡣\n");
	if( me->query("mana") < 1200 )
		return notify_fail("�㷨�����㡣\n");
	if( me->query_skill("bainiao-jian",1) < 180 )
		return notify_fail("��İ��񽣷�̫���ˡ�\n");
	if( me->query_skill("spells") < 200 )
		return notify_fail("��ķ���̫���ˡ�\n");
	if(target->is_busy())
           	return notify_fail("�Է�����æ�ң�������˼������ı��ݣ���\n");
      	weapon = me->query_temp("weapon");
        ap = me->query("combat_exp")/10000;
        ap = 1+random(ap);
	dp = target->query("combat_exp")/12000;
        msg = HIM"$N�������˸��������������˼��京��Ϳ����������������" + weapon->name() + HIM"��һָ��\n"NOR;
        msg += weapon->name() + HIC"�Ȼ��������������������໥������\n"NOR;
        if( ap > dp / 3 )
        {
        	msg += HIB"$n����ͻ�������İ���֮�������ķ����ң�����ʧ�˷��硣\n"NOR;
        	target->start_busy(3+random(3));
        }
        else if( ap > dp / 5 )
        {
        	msg += HIY"$n��æ����һ����Х����$N�İ���֮�����˸�����൱��˭Ҳûռ��ʲô���ˡ�\n"NOR;
        	target->start_busy(1);
        	me->start_busy(1);
        }
        else
        {
        	msg += HIR"$n���Ų�æ�����з���һ��Х������$N�İ���֮������$nѹ���ˡ�\n"NOR;
        	me->start_busy(1);
        }
        me->add("force",-100);
        me->add("mana",-100);
        message_vision(msg, me, target);
        return 1;
}