#ifndef L2SKILL_H_
#define L2SKILL_H_

class L2Skill
{
public:
	L2Skill(): isPassive(1), id(0), level(0) {}
	~L2Skill() {}
public:
	int isPassive;
	unsigned int id;
	unsigned int level;
};

#endif
