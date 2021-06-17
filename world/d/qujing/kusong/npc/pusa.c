//Cracked by Roath

inherit NPC;
#include <ansi.h>
void create()
{
	set_name("��������", ({ "guanyin pusa", "guanyin", "pusa" }));
	set("title", "�ȿ���Ѵ�ȴ�");
	set("long", @LONG
��Բ�ĵ£�����������ü��С�£�����˫�ǡ�����������
ޥ�԰����١���������٤ɽ�ϴȱ�������������������
LONG);
	set("gender", "Ů��");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "ƶɮ");
	set("rank_info/respect", "��������");
	set("class", "bonze");
	set("family/family_name","�Ϻ�����ɽ");
  set("str",60);
	set("per",100);//means no rong-mao description.
	set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
	set("force", 4000);
	set("max_force", 2000);
	set("force_factor", 240);
	set("max_mana", 3000);
	set("mana", 6000);
	set("mana_factor", 240);
	set("combat_exp", 2000000);
	set("daoxing", 10000000);

	set_skill("literate", 260);
	set_skill("spells", 260);
	set_skill("buddhism", 260);
	set_skill("unarmed", 260);
	set_skill("jienan-zhi", 260);
	set_skill("dodge", 260);
	set_skill("lotusmove", 260);
	set_skill("parry", 260);
	set_skill("force", 260);
	set_skill("lotusforce", 260);
	set_skill("staff", 260);
	set_skill("lunhui-zhang", 260);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "unarmed", "lingxi" :),
		(: perform_action, "unarmed", "rulai" :),
	}) );

	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	//carry_object("/d/nanhai/obj/nine-ring")->wield();
}

void announce_success (object who)
{
  
  int i;

  if(!who) return;

  if (who->query("combat_exp") < 10000)
    return;
  if (who->query("obstacle/huoyun") == "done")
    return;
  if (! who->query_temp("obstacle/hong_killed"))
    return;
  if (who->query("obstacle/wuji") != "done")
    return;  

  	i = random(700);
  who->add("obstacle/number",1);
  who->set("obstacle/huoyun","done");
  who->add("daoxing",i+3000);
  command("chat "+who->query("name")+"���ɽ����ƶ�.�շ��캢��");
  message("channel:chat",HIY"������ն������������(guanyin pusa)��"+who->query("name")+"��������ȡ��[1;37m��ʮ�Ĺأ�\n"NOR,users());
  tell_object (who,"��Ӯ����"+chinese_number(3)+"��"+
              chinese_number(i/4)+"��"+
               chinese_number((i-(i/4)*4)*3)+"ʱ���ĵ��У�\n");
  who->save();
}
void die()
{
        if( environment() ) 
        	message("sound", "\n��������һ����ͷ���ԣ������ƣ��ǲ�������������ȥ�ˡ�����\n\n", environment());
	destruct(this_object());
}
void unconcious()
{
	die();
}