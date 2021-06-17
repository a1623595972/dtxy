#include <ansi.h>
inherit NPC;


void create()
{
    set_name(HIC "ͨ�����" NOR, ({"tongtian jiaozhu", "tongtian", "jiaozhu"}));
    set("title", HIG "�������" NOR);
    set("long", "ԭ����Ԫʼ�����ʦ�ܣ�������а����\n");
    set("gender", "����");
    set("age", 13500);
    set("str", 40);
    set("per", 40);
    set("attitude", "peaceful");
    set("combat_exp", 10000000);
    set("daoxing", 10000000);
    set("eff_kee", 10000);
    set("eff_sen", 10000);
    set("max_kee", 10000);
    set("max_sen", 10000);
    set("sen", 10000);
    set("kee", 10000);
    set("max_force", 10000);
    set("max_mana", 10000);
    set("mana", 10000);
    set("force", 20000);
    set("force_factor",  500);
    set("mana_factor", 500);
    set_skill("dao", 351 );
    set_skill("spells", 321);
    set_skill("force", 301);
    set_skill("yaofa", 351);
    set_skill("whip", 301);
    set_skill("staff", 301);
    set_skill("blade", 301);
    set_skill("spear", 301);
    set_skill("hammer", 301);
    set_skill("dengxian-dafa", 351);
    set_skill("pansi-dafa", 351);
    set_skill("jiuyin-xinjing", 351);
    set_skill("ningxie-force", 351);
    set_skill("huntian-qigong", 351);
    set_skill("stick", 301);
    set_skill("dodge", 301);
    set_skill("unarmed", 301);
    set_skill("parry", 301);
    set_skill("sword", 301);
    set_skill("pingtian-dafa", 351);
    set_skill("huomoforce", 351);
    set_skill("fork", 301);
      map_skill("force", "huomoforce");
      map_skill("spells", "dao");
    set("class","yaomo");
    set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
        (: cast_spell, "light" :),
        (: cast_spell, "thunder" :),
        (: cast_spell, "dingshen" :),
        (: cast_spell, "fenshen" :),
(: exert_function, "fire" :)
}));
      setup();
   
}

int accept_fight(object me)
{

        return 1;
}

int recognize_apprentice(object me)
{
      object ob = this_player();
      
        if (!(int)ob->query_temp("mark/ħ"))
             return notify_fail( HIR "������" HIC "ͨ�����" HIR "��ɱ���㣡\n"NOR);
        if( ( ob->query("family/family_name") != "��˿��"
            && ob->query("family/family_name") != "�ݿ�ɽ�޵׶�"
            && ob->query("family/family_name") != "��ѩɽ"
            && ob->query("family/family_name") != "���ƶ�")
            || ob->query("combat_exp")  < 2000000 ) 
             return notify_fail( HIR "������" HIC "ͨ�����" HIR "��ɱ���㣡\n"NOR);

             ob->add_temp("mark/ħ", -1);
               return 1;
}
void unconcious()
{
	die();
}
void die()
{
	object who = query_temp("last_damage_from");
  	if( who->query_temp("quzhu/ttjz") )  
	{
	  	who->delete_temp("quzhu");
	  	if( random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
	  	{
	  		who->add("quzhu_known",1);
	  		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��Ԫʼ����(yuanshi tianzun)��" + who->name() + "ɱ��ͨ������������ƽ�ʮ������ȫ������"+HIR"[������ħ]"+HIC"��������\n\n\n"NOR,users());	
	  	}	
	  	else
	  	{
	  		who->set("quzhu_cant",1);
	  		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��Ԫʼ����(yuanshi tianzun)��" + who->name() + "ɱ��ͨ������������ƽ�ʮ���󣬿�ϧ������ȫ����"+HIR"[������ħ]"+HIC"��������\n\n\n"NOR,users());	
	  	}
	}
	::die();
}