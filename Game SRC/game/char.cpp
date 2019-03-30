// find
	tab.gold		= GetGold()

// add after
#ifdef ENABLE_REBIRTH_SYSTEM
	tab.rebirt		= GetRebirth();
#endif

// find
		pack.points[i] = GetPoint(i);

// add after
#ifdef ENABLE_REBIRTH_SYSTEM
	pack.points[POINT_REBIRTH] = GetRebirth();
#endif

// find
void CHARACTER::SetLevel(BYTE level)
{
	[...]
}

// add after

#ifdef ENABLE_REBIRT_SYSTEM
void CHARACTER::SetRebirt(BYTE rebirt)
{
	m_points.rebirt = rebirt;

	if (IsPC() 
		#ifdef OFFLINE_SHOP
		|| IsPrivShop()
		#endif
		)
	{
		if (GetMyShop())
			Save();

		UpdatePacket();
	}
}
#endif

// find
	SetGold(t->gold);

// add after
#ifdef ENABLE_REBIRT_SYSTEM
	SetRebirt(t->rebirt);
#endif

// find
if (gPlayerMaxLevel <= GetLevel())

// replace

					#ifdef ENABLE_REBIRT_SYSTEM
					if (GetLevel() >= gPlayerMaxLevel)
					{
					if (block_exp)
						{
							return;
						} 
						//DWORD next_exp = GetNextRebirtExp();
						if (GetRebirt() < REBIRT_MAX)
						{
							if (GetRebirt() < 6)
								amount /= 2;
							else
								amount /= 4;

							if (GetLevel() >= gPlayerMaxLevel && (exp + amount) >= next_exp)
							{
								SetRebirt(GetRebirt()+1);
								SetExp(0);

								if (IsPC())
								{
									if (GetRebirt() == 1 || 
										GetRebirt() == 2 || 
										GetRebirt() == 3 || 
										GetRebirt() == 4 || 
										GetRebirt() == 5)
									{
										EffectPacket(SE_DUEL_SENDER);
									}
									else if (GetRebirt() == 6 || 
										GetRebirt() == 7 || 
										GetRebirt() == 8 || 
										GetRebirt() == 9 || 
										GetRebirt() == 10)
									{
										EffectPacket(SE_DUEL_RECEIVER);
									}

									int hpver = GetHP();

									if (GetRebirt() == 3)
									{
										PointChange(POINT_STAT, 3, false);
										AddAffect(AFFECT_COLLECT, POINT_MAX_HP, hpver* 2/100 , 0, 60*60*24*365*60, 0, false);
									}

									if (GetRebirt() == 4)
									{
										PointChange(POINT_STAT, 2, false);
										AddAffect(AFFECT_COLLECT, POINT_MAX_HP, hpver* 4/100 , 0, 60*60*24*365*60, 0, false);
									}

									if (GetRebirt() == 7)
									{
										PointChange(POINT_STAT, 3, false);
										AddAffect(AFFECT_COLLECT, POINT_MAX_HP, hpver* 6/100 , 0, 60*60*24*365*60, 0, false);
									}

									if (GetRebirt() == 10)
									{
										PointChange(POINT_STAT, 2, false);
										AddAffect(AFFECT_COLLECT, POINT_MAX_HP, hpver* 8/100 , 0, 60*60*24*365*60, 0, false);
										AddAffect(AFFECT_COLLECT, POINT_ATTBONUS_HUMAN, 10, 0, 60*60*24*365*60, 0, false);
									}


									ChatPacket(CHAT_TYPE_INFO, LC_TEXT("rebirt_eklendi"));
									PointsPacket();
								}

								return;
							}
						}
						else
						{
							sys_log(1, "%s Rebirth son seviyede.", GetName());
							return;
						}
					}
					else if (gPlayerMaxLevel <= GetLevel() && REBIRT_MAX <= GetRebirt())
					{
						if (GetExp() > 0)
							SetExp(0);

						return;
					}
					#else
					if (gPlayerMaxLevel <= GetLevel())
						return;
					if (block_exp)
						return;
					#endif

// find
		case POINT_GOLD:

// add after
		#ifdef ENABLE_REBIRT_SYSTEM
		case POINT_REBIRT:
			{
				const int16_t nTotalRebirt = static_cast<int16_t>(GetRebirt()) + static_cast<int16_t>(amount);

				if (nTotalRebirt < 0)
				{
					sys_err("[OVERFLOW_CHEQUE] Rebirt eksi deger rebirti %u Name %s ", GetRebirt(), GetName());
					return;
				}

				if (nTotalRebirt >= REBIRT_MAX)
				{
					sys_err("[OVERFLOW_CHEQUE] Rebirt max seviyede rebirti %u Name %s ", GetRebirt(), GetName());
					return;
				}

				if (LC_IsNewCIBN() && amount > 0)
				{
					if (IsOverTime(OT_NONE))
					{
						dev_log(LOG_DEB0, "<REBIRT_LOG> %s = NONE", GetName());
					}
					else if (IsOverTime(OT_3HOUR))
					{
						amount = (amount / 2);
						dev_log(LOG_DEB0, "<REBIRT_LOG> %s = 3HOUR", GetName());
					}
					else if (IsOverTime(OT_5HOUR))
					{
						amount = 0;
						dev_log(LOG_DEB0, "<REBIRT_LOG> %s = 5HOUR", GetName());
					}
				}

				SetRebirt(GetRebirt() + amount);
				val = GetRebirt();
			}
			break;
		#endif

// find
int	CHARACTER::GetSkillPowerByLevel(int level, bool bMob) const
{
[...]
}

// add after
#ifdef ENABLE_REBIRT_SYSTEM
DWORD CHARACTER::GetNextRebirtExp() const
{
	if (REBIRT_MAX < GetRebirt())
		return 2100000000;
	else if (GetRebirt() == 0)
		return exp_rebirt_table[1];
	else
		return exp_rebirt_table[GetRebirt()];
}
#endif

// find
	pack2.sAlignment = 0;

// add after
#ifdef ENABLE_REBIRT_SYSTEM
	pack2.bRebirt = 0;
#endif

// find
	pack.dwMountVnum	= GetMountVnum();

// add after
#ifdef ENABLE_REBIRT_SYSTEM
	pack.bRebirt = GetRebirt();
#endif