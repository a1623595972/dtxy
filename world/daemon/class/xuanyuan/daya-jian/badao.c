//�ε���
//lestat for daya-jian
//ȡ���ձ�����ά���ڼ䴫˵�е�ɱ������彣�ĵľ�ѧ
//��彣�ĵĽ������ڷ���������,ά���ڼ�ųưε���
//�����佣������,���аε�������,Ҳ�ǴºŰε��������
//����Ϊ�ձ�������һ����

#include <ansi.h>

inherit SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon;
	if( me->query("lunhui_zhuanshi") < 5 )
		return notify_fail("�㻹û��ת����Σ��������á��ε�������\n");
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("�ε���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if(!weapon->query("badao"))
            return notify_fail("û�����е���ô�ðε���? \n");
        if((int) me->query_skill("daya-jian",1) < 500)
		return notify_fail("��Ĵ��Ž�������500������ûѧ��ε�����\n");
        if( (int)me->query("combat_exp") < (int)target->query("combat_exp")/2  )
                return notify_fail("�Է�����ǿ̫���ˣ����Ǳ������ɣ�\n");
        if(me->query_temp("start_qijian")) 
                return notify_fail("���Ѿ�����������ָ�����ν����ˣ�\n");
	message_vision(RED"$N�ս�����Ŀ��ת���ض���$n��׼����������һ����\n"NOR,me,target);
        me->start_call_out( (: call_other, __FILE__, "kill_him", me, target :), 5);
	me->start_busy(5);
//        target->start_busy(7);
if (userp(target))
       target->start_busy(4);
if (!userp(target))
target->start_busy(6);
	return 1;
}
void kill_him(object me, object target)
{
	string msg,str;
         int damage, ap, dp,qixue,eff_qi,max_qi,qi_pcg,force;
        eff_qi=me->query("eff_kee");
        max_qi=me->query("max_kee");
        qi_pcg=eff_qi*100/max_qi;
      force=target->query("force");
	if(me->is_fighting() && target->is_fighting() &&
	environment(me) == environment(target))
	{
//msg = HIB "$N�ν����ʣ�һ������"NOR+HIC"����"NOR+HIB"������$n"NOR+HIB"ֻ��������һ�����ѱ�����������ն������" ;
msg = HIB "$N�ν����ʣ�һ������"NOR+HIC"����"NOR+HIB"������$n"NOR+HIB"ֻ��������һ��������" ;
msg +=  "\nһ��Ѫ����ӿ��������$N��ָ���������վ�ţ�һ�ε���Ѫ���������е��ϵ��£���\n" NOR;

	message_vision(msg, me, target);
if (!userp(target))
      str=target->query("name")+"��"+me->query("name")+"�ô�˵�е�ɱ�˽���:"HIC"�ε���"NOR+HIM"ն�ˣ�ʬ���������ϣ�";
if (userp(target))
         str=target->query("name")+"��"+me->query("name")+"�ô�˵�е�ɱ�˽���:"HIC"�ε���"NOR+HIM"���ˣ�";
	message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
//        target->die();
if (userp(target))
{
  target->set("kee", 0);
  target->set("sen",0);
  target->set("eff_kee",eff_qi*random(5)/10);
target->set("force",1);
  target->set("eff_sen",me->query("eff_sen")*random(5)/10);
call_out("huifu",5,target,force);
}
if (!userp(target)) {
  if (target->is_manmade_npc()) {
      target->set("combat_exp", 0);
      target->set("daoxing", 0);
  }
 target->die();
}
/*
{
  target->set("kee", -1);
  target->set("sen",-1);
target->set("eff_kee",eff_qi*random(5)/10);
 target->set("eff_sen",me->query("eff_sen")*random(5)/10);
}
*/
	me->set("kee", 1);
        me->set("eff_kee",1+eff_qi*random(10)/100);
        me->set("sen",1);
        me->set("eff_sen",1+me->query("eff_sen")*random(10)/100);
        me->set("force",0);
	}
	return ;
}

void huifu(object target,int force)
{
 if (target)
   target->set("force",force);
}