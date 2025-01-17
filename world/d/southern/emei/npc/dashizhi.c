//created by greenwc
inherit NPC;
inherit F_MASTER;

#include <ansi.h>
void create()
{
  set_name("如来佛祖", ({"rulai fo", "rulai", "fo"}));
  set("long", "大慈大悲灵山雷音古刹佛祖多陀阿伽陀如来佛爷。\n");
//人并称西方三神。
//LONG);
set("title", "佛祖多陀阿伽陀");
  set("gender", "男性");
  set("age", 400);
  set("str", 40);
  set("per", 40);
  set("int", 30);
  set("cor", 50);
  set("cps", 40);
       set_skill("literate", 300);
        set_skill("spells", 300);
        set_skill("buddhism", 300);
        set_skill("unarmed", 300);
        set_skill("jienan-zhi", 300);
        set_skill("dodge", 300);
        set_skill("lotusmove", 300);
        set_skill("parry", 300);
        set_skill("force", 300);
        set_skill("lotusforce", 300);
        set_skill("staff", 300);
        set_skill("lunhui-zhang", 300);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
        map_skill("parry", "lunhui-zhang");
        map_skill("staff", "lunhui-zhang");
        set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
                        (: perform_action, "staff", "pudu" :),
                        (: perform_action, "staff", "chaodu" :),
	}) );
           set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
        set("force", 40000);
        set("max_force", 20000);
        set("force_factor", 1000);
        set("max_mana", 30000);
        set("mana", 60000);
        set("mana_factor", 1500);
        set("combat_exp", 20000000);
	set("daoxing", 10000000);

        create_family("南海普陀山", 1, "佛祖");
  setup();

        carry_object("/d/nanhai/obj/nine-ring")->wield();
  carry_object("/d/obj/cloth/jia_sha")->wear();
}
void init()
{
        object ob = this_player();
        remove_call_out("check");
        call_out("check",1,ob);
}

int accept_fight(object me)
{
  command("say 施主玩笑了\n");
return 0;
}

int attempt_apprentice(object ob)
{
	string myname=RANK_D->query_respect(ob);
            if (!((string)ob->query("bonze/class") =="bonze" )) {
		command("say 我佛门神通广大，" + RANK_D->query_respect(ob) + "欲成正果，先入我门。\n");
return 0;
}
if (((int)ob->query_skill("buddhism", 1) < 100 )) {
      command("say 施主对佛法的研究还不够精深！");
return 0;
}
if (ob->query("obstacle/number") < 26) {
        command("say 这位" + RANK_D->query_respect(ob) + "你还是先出去闯荡一番吧！\n");
        command("sigh");
        return 0;
        }
	command("pat " + ob->query("id") );
	command("say 好！这才是我佛门的好弟子。只要多加努力，定可早成正果。\n");
	command("recruit " + ob->query("id") );
ob->set("title", HIY"慈光普渡佛祖"NOR);
        return 1; 
}

void die()
{
        if( environment() ) {
        message("sound", "\n\n如来佛祖摇头叹道：冤孽！真是冤孽！n\n", environment());
        command("sigh");
        message("sound", "\n如来佛祖驾祥云，登彩雾，径往西方去了。。。\n\n", environment());
}

	destruct(this_object());
}

void check(object ob)
{
        object mo;
        if(!objectp(ob))
        	return;
        if(ob->query("family/family_name") != "南海普陀山")
           	return;
        if(!userp(ob))
           	return;
        if( ob->query("fmtd_cant") )
           	return;   
        if( !ob->query_temp("fmtd/canwu") )
           	return;
        if( ob->query_temp("fmtd/canwu") == 1 )
        {
        	command("say 不错，竟然能领悟到佛魔的本质。");
		command("say 自佛教创建以来，众佛普度众生，除魔卫道，往往到了最后还不知道何以为魔。");
		command("say 到得后来，世人更是将修炼方式特别的武功，称为魔功，凡是修习者，皆归为魔类。");
		command("say 此大谬也！再后来修习这些功法的人，由于不被众人接收，渐渐行为偏激，甚至入了魔道。");
		command("say 本要普渡众生，却把一部分人逼入魔道，岂不是反而违背了初衷！");
		command("say 此时这舍身崖上，正有这样一人，你切去渡化了他，回来后我传你六字真言法阵。");
		ob->set_temp("fmtd/canwu",2);
		mo = new("/d/southern/emei/npc/mo");
		mo->copy_status(mo,ob,10);
		mo->move("/d/southern/emei/sheshenyan");
		return;
        }
        else if( ob->query_temp("fmtd/canwu") == 2 )
        {
        	command("say 此人武功高强，你要小心。");
        	return;
        }
        else
        {
		command("say 很好，相信你通过此事对佛魔的理解也更加深入了，我这就传你六字真言法阵。");
		message_vision(HIC"$N佛手一张，生出朵朵白莲，白莲首尾相连，不停转动，似是无有穷尽。\n"NOR,this_object());
		command("say 六字真言个有妙用，但是相互关联，息息相通，如果将六字真言按照不同的次序排列自有不同的效果。");
		message_vision(HIC"$n看着$N手上的真言，听着$N的佛音，全身筋脉隐隐震动，有所领悟。\n"NOR,this_object(),ob);
		message_vision(HIC"$n眼前一花，似乎进入了一个完全陌生的境界。\n"NOR,this_object(),ob);
		ob->start_busy(15);
		if( random(ob->query("int")) > 30 - random( ob->query("lunhui_zhuanshi") ) )
			call_out("finish1",10,ob);
		else
			call_out("finish2",10,ob);
		return;
        }
        return;
}
void finish1( object me )
{
	message_vision(HIC"$N觉得那些真言彷佛和本身内力息息相通，真言带动不同的经脉震动。\n" NOR,me);
	message_vision(HIC"$N心神逐渐空明，无喜无忧，真言间的脉络慢慢显现了出来！\n" NOR,me);
	message_vision(HIC"$N觉得禅意已尽，无喜无忧的境界立时消散而去！\n" NOR,me);
	me->delete_temp("fmtd");
	me->add("fmtd_known",1);
	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗如来佛祖(rulai fo)：" + me->name() + "渡化世人，领悟了"+HIB"[佛魔同道]"+HIC"绝学的最高境界！\n\n\n"NOR,users());
	command("say 日后多做善举，渡化苦难众生！");
	return ;
}

void finish2( object me )
{
	message_vision(HIC"$N觉得那些真言彷佛和本身内力息息相通，真言带动不同的经脉震动。\n" NOR,me);
	message_vision(HIC"$N努力想去看清真言之间的脉络联系，却只见真言纵横交错！\n" NOR,me);
	message_vision(HIC"$N体内真力随着真言四处冲突，难受异常，$N一下从禅境中惊醒！\n" NOR,me);
	me->delete_temp("fmtd");
	me->set("fmtd_cant",1);
	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗如来佛祖(rulai fo)：" + me->name() + "以佛法渡化世人，却无缘"+HIB"[佛魔同道]"+HIC"绝学的最高境界！\n\n\n"NOR,users());
	command("sigh " + me->query("id"));
	command("say 你悟性不足，莫要强求，佛门武功博大精深，足够你学的了！");
	return ;
}