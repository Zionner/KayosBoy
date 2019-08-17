#include "CPU.hpp"

CPU::CPU() :
	mRegisterAF(mRegisterA, mRegisterF),
	mRegisterBC(mRegisterB, mRegisterC),
	mRegisterDE(mRegisterD, mRegisterE),
	mRegisterHL(mRegisterH, mRegisterL)
{

}

// ADC
void CPU::ADC()
{

}

void CPU::ADC(uint8_t val)
{

}

void CPU::ADC(ByteRegister& val)
{

}

void CPU::ADC(KayosBoyPtr& ptrToVal)
{

}

// ADD
void CPU::ADD()
{

}

void CPU::ADD_SP()
{

}

void CPU::ADD(uint8_t val)
{

}

void CPU::ADD(uint16_t val)
{

}

void CPU::ADD(ByteRegister& val)
{

}

void CPU::ADD(TwoByteRegister& val)
{

}

void CPU::ADD(PairedByteRegister& val)
{

}

void CPU::ADD(KayosBoyPtr& ptrToVal)
{

}

// AND
void CPU::AND()
{

}

void CPU::AND(uint8_t val)
{

}

void CPU::AND(ByteRegister& val)
{

}

void CPU::AND(KayosBoyPtr& ptrToVal)
{

}

// BIT
void CPU::BIT(uint8_t bit, ByteRegister& registerToTest)
{

}

void CPU::BIT(uint8_t bit, KayosBoyPtr& addressToByteToTest)
{

}

// CALL
void CPU::CALL()
{

}

void CPU::CALL(uint8_t flagCondition)
{

}

// CFF
void CPU::CFF()
{

}

// CPL
void CPU::CPL()
{

}

// DAA
void CPU::DAA()
{

}

// DEC
void CPU::DEC(ByteRegister& val)
{

}

void CPU::DEC(TwoByteRegister& val)
{

}

void CPU::DEC(PairedByteRegister& val)
{

}

void CPU::DEC(KayosBoyPtr& ptrToVal)
{

}

// DI
void CPU::DI()
{

}

// EI
void CPU::EI()
{

}

// CP
void CPU::CP()
{

}

void CPU::CP(uint8_t val)
{

}

void CPU::CP(ByteRegister& val)
{

}

void CPU::CP(KayosBoyPtr& ptrToVal)
{

}

// HALT
void CPU::HALT()
{

}

// INC
void CPU::INC(ByteRegister& val)
{

}

void CPU::INC(TwoByteRegister& val)
{

}

void CPU::INC(PairedByteRegister& val)
{

}

void CPU::INC(KayosBoyPtr& ptrToVal)
{

}

// JP
void CPU::JP()
{

}

void CPU::JP(uint8_t flagCondition)
{

}

void CPU::JP(KayosBoyPtr& ptr)
{

}

// JR
void CPU::JR()
{

}

void CPU::JR(uint8_t flagCondition)
{

}

// LD
void CPU::LD_PC(ByteRegister& registerToSet)
{

}

void CPU::LD_PC(KayosBoyPtr& ptrToSet)
{

}

void CPU::LD_PC(PairedByteRegister& val)
{

}

void CPU::LD_PC(TwoByteRegister& registerToSet)
{

}

void CPU::LD_PCAddress(ByteRegister& registerToSet)
{

}

void CPU::LD_WriteToPCAddress(ByteRegister& registerToSet)
{

}

void CPU::LD(ByteRegister& registerToSet, ByteRegister& val)
{

}

void CPU::LD(ByteRegister& registerToSet, KayosBoyPtr& val)
{

}

void CPU::LD(TwoByteRegister& registerToSet, PairedByteRegister& val)
{

}

void CPU::LD(KayosBoyPtr& ptrToSet, ByteRegister& val)
{

}

void CPU::LD(KayosBoyPtr& ptrToSet, TwoByteRegister& val)
{

}

// LDD
void CPU::LDD(ByteRegister& registerToSet, KayosBoyPtr& val)
{

}

void CPU::LDD(KayosBoyPtr& ptrToSet, ByteRegister& val)
{

}

// LDH
void CPU::LDH_A()
{

}

void CPU::LDH_PC()
{

}

void CPU::LDH_C()
{

}

void CPU::LDH_CAddr_A()
{

}

// LDHL
void CPU::LDHL()
{

}

// LDI
void CPU::LDI(ByteRegister& registerToSet, KayosBoyPtr& val)
{

}

void CPU::LDI(KayosBoyPtr& addressToSet, ByteRegister& val)
{

}

// NOP
void CPU::NOP()
{

}

// OR
void CPU::OR()
{

}

void CPU::OR(uint8_t val)
{

}

void CPU::OR(ByteRegister& val)
{

}

void CPU::OR(KayosBoyPtr& ptrToVal)
{

}

// POP
void CPU::POP(PairedByteRegister& val)
{

}

// PUSH
void CPU::PUSH(PairedByteRegister& val)
{

}

// RES
void CPU::RES(uint8_t bit, ByteRegister& registerToReset)
{

}

void CPU::RES(uint8_t bit, KayosBoyPtr& addressToByteToReset)
{

}

// RET
void CPU::RET()
{

}

void CPU::RET(uint8_t flagCondition) // Conditions could be handled via enums. Right now it's being handled by bit comparisons.
{

}

// RETI
void CPU::RETI()
{

}

// RLA
void CPU::RLA()
{

}

// RLCA
void CPU::RLCA()
{

}

// RLC
void CPU::RLC(ByteRegister& registerToRotate)
{

}

void CPU::RLC(KayosBoyPtr& addressToByteToRotate)
{

}

// RL
void CPU::RL(ByteRegister& registerToRotate)
{

}

void CPU::RL(KayosBoyPtr& addressToByteToRotate)
{

}

// RRA
void CPU::RRA()
{

}

// RRCA
void CPU::RRCA()
{

}

// RRC
void CPU::RRC(ByteRegister& registerToRotate)
{

}

void CPU::RRC(KayosBoyPtr& addressToByteToRotate)
{

}

// RR
void CPU::RR(ByteRegister& registerToRotate)
{

}

void CPU::RR(KayosBoyPtr& addressToByteToRotate)
{

}

// RST
void CPU::RST(uint8_t offset)
{

}

// SBC
void CPU::SBC()
{

}

void CPU::SBC(uint8_t val)
{

}

void CPU::SBC(ByteRegister& val)
{

}

void CPU::SBC(KayosBoyPtr& ptrToVal)
{

}

// SCF
void CPU::SCF()
{

}

// SET
void CPU::SET(uint8_t bit, ByteRegister& registerToSet)
{

}

void CPU::SET(uint8_t bit, KayosBoyPtr& addressToByteToSet)
{

}

// SLA
void CPU::SLA(ByteRegister& registerToShift)
{

}

void CPU::SLA(KayosBoyPtr& addressToByteToShift)
{

}

// SRA
void CPU::SRA(ByteRegister& registerToShift)
{

}

void CPU::SRA(KayosBoyPtr& addressToByteToShift)
{

}

// SRL
void CPU::SRL(ByteRegister& registerToShift)
{

}

void CPU::SRL(KayosBoyPtr& addressToByteToShift)
{

}

// SWAP
void CPU::SWAP(ByteRegister& registerToSwap)
{

}

void CPU::SWAP(KayosBoyPtr& addressToByteToSwap)
{

}

// STOP
void CPU::STOP()
{

}

// SUB
void CPU::SUB()
{

}

void CPU::SUB(uint8_t val)
{

}

void CPU::SUB(ByteRegister& val)
{

}

void CPU::SUB(KayosBoyPtr& ptrToVal)
{

}

// XOR
void CPU::XOR()
{

}

void CPU::XOR(uint8_t val)
{

}

void CPU::XOR(ByteRegister& val)
{

}

void CPU::XOR(KayosBoyPtr& ptrToVal)
{

}

// OPCODES 0X
void CPU::_00()
{

}

void CPU::_01()
{

}

void CPU::_02()
{

}

void CPU::_03()
{

}

void CPU::_04()
{

}

void CPU::_05()
{

}

void CPU::_06()
{

}

void CPU::_07()
{

}

void CPU::_08()
{

}

void CPU::_09()
{

}

void CPU::_0A()
{

}

void CPU::_0B()
{

}

void CPU::_0C()
{

}

void CPU::_0D()
{

}

void CPU::_0E()
{

}

void CPU::_0F()
{

}


// OPCODES 1X
void CPU::_10()
{

}

void CPU::_11()
{

}

void CPU::_12()
{

}

void CPU::_13()
{

}

void CPU::_14()
{

}

void CPU::_15()
{

}

void CPU::_16()
{

}

void CPU::_17()
{

}

void CPU::_18()
{

}

void CPU::_19()
{

}

void CPU::_1A()
{

}

void CPU::_1B()
{

}

void CPU::_1C()
{

}

void CPU::_1D()
{

}

void CPU::_1E()
{

}

void CPU::_1F()
{

}


// OPCODES 2X
void CPU::_20()
{

}

void CPU::_21()
{

}

void CPU::_22()
{

}

void CPU::_23()
{

}

void CPU::_24()
{

}

void CPU::_25()
{

}

void CPU::_26()
{

}

void CPU::_27()
{

}

void CPU::_28()
{

}

void CPU::_29()
{

}

void CPU::_2A()
{

}

void CPU::_2B()
{

}

void CPU::_2C()
{

}

void CPU::_2D()
{

}

void CPU::_2E()
{

}

void CPU::_2F()
{

}


// OPCODES 3X
void CPU::_30()
{

}

void CPU::_31()
{

}

void CPU::_32()
{

}

void CPU::_33()
{

}

void CPU::_34()
{

}

void CPU::_35()
{

}

void CPU::_36()
{

}

void CPU::_37()
{

}

void CPU::_38()
{

}

void CPU::_39()
{

}

void CPU::_3A()
{

}

void CPU::_3B()
{

}

void CPU::_3C()
{

}

void CPU::_3D()
{

}

void CPU::_3E()
{

}

void CPU::_3F()
{

}


// OPCODES 4X
void CPU::_40()
{

}

void CPU::_41()
{

}

void CPU::_42()
{

}

void CPU::_43()
{

}

void CPU::_44()
{

}

void CPU::_45()
{

}

void CPU::_46()
{

}

void CPU::_47()
{

}

void CPU::_48()
{

}

void CPU::_49()
{

}

void CPU::_4A()
{

}

void CPU::_4B()
{

}

void CPU::_4C()
{

}

void CPU::_4D()
{

}

void CPU::_4E()
{

}

void CPU::_4F()
{

}


// OPCODES 5X
void CPU::_50()
{

}

void CPU::_51()
{

}

void CPU::_52()
{

}

void CPU::_53()
{

}

void CPU::_54()
{

}

void CPU::_55()
{

}

void CPU::_56()
{

}

void CPU::_57()
{

}

void CPU::_58()
{

}

void CPU::_59()
{

}

void CPU::_5A()
{

}

void CPU::_5B()
{

}

void CPU::_5C()
{

}

void CPU::_5D()
{

}

void CPU::_5E()
{

}

void CPU::_5F()
{

}


// OPCODES 6X
void CPU::_60()
{

}

void CPU::_61()
{

}

void CPU::_62()
{

}

void CPU::_63()
{

}

void CPU::_64()
{

}

void CPU::_65()
{

}

void CPU::_66()
{

}

void CPU::_67()
{

}

void CPU::_68()
{

}

void CPU::_69()
{

}

void CPU::_6A()
{

}

void CPU::_6B()
{

}

void CPU::_6C()
{

}

void CPU::_6D()
{

}

void CPU::_6E()
{

}

void CPU::_6F()
{

}


// OPCODES 7X
void CPU::_70()
{

}

void CPU::_71()
{

}

void CPU::_72()
{

}

void CPU::_73()
{

}

void CPU::_74()
{

}

void CPU::_75()
{

}

void CPU::_76()
{

}

void CPU::_77()
{

}

void CPU::_78()
{

}

void CPU::_79()
{

}

void CPU::_7A()
{

}

void CPU::_7B()
{

}

void CPU::_7C()
{

}

void CPU::_7D()
{

}

void CPU::_7E()
{

}

void CPU::_7F()
{

}


// OPCODES 8X
void CPU::_80()
{

}

void CPU::_81()
{

}

void CPU::_82()
{

}

void CPU::_83()
{

}

void CPU::_84()
{

}

void CPU::_85()
{

}

void CPU::_86()
{

}

void CPU::_87()
{

}

void CPU::_88()
{

}

void CPU::_89()
{

}

void CPU::_8A()
{

}

void CPU::_8B()
{

}

void CPU::_8C()
{

}

void CPU::_8D()
{

}

void CPU::_8E()
{

}

void CPU::_8F()
{

}


// OPCODES 9X
void CPU::_90()
{

}

void CPU::_91()
{

}

void CPU::_92()
{

}

void CPU::_93()
{

}

void CPU::_94()
{

}

void CPU::_95()
{

}

void CPU::_96()
{

}

void CPU::_97()
{

}

void CPU::_98()
{

}

void CPU::_99()
{

}

void CPU::_9A()
{

}

void CPU::_9B()
{

}

void CPU::_9C()
{

}

void CPU::_9D()
{

}

void CPU::_9E()
{

}

void CPU::_9F()
{

}


// OPCODES AX
void CPU::_A0()
{

}

void CPU::_A1()
{

}

void CPU::_A2()
{

}

void CPU::_A3()
{

}

void CPU::_A4()
{

}

void CPU::_A5()
{

}

void CPU::_A6()
{

}

void CPU::_A7()
{

}

void CPU::_A8()
{

}

void CPU::_A9()
{

}

void CPU::_AA()
{

}

void CPU::_AB()
{

}

void CPU::_AC()
{

}

void CPU::_AD()
{

}

void CPU::_AE()
{

}

void CPU::_AF()
{

}


// OPCODES BX
void CPU::_B0()
{

}

void CPU::_B1()
{

}

void CPU::_B2()
{

}

void CPU::_B3()
{

}

void CPU::_B4()
{

}

void CPU::_B5()
{

}

void CPU::_B6()
{

}

void CPU::_B7()
{

}

void CPU::_B8()
{

}

void CPU::_B9()
{

}

void CPU::_BA()
{

}

void CPU::_BB()
{

}

void CPU::_BC()
{

}

void CPU::_BD()
{

}

void CPU::_BE()
{

}

void CPU::_BF()
{

}


// OPCODES CX
void CPU::_C0()
{

}

void CPU::_C1()
{

}

void CPU::_C2()
{

}

void CPU::_C3()
{

}

void CPU::_C4()
{

}

void CPU::_C5()
{

}

void CPU::_C6()
{

}

void CPU::_C7()
{

}

void CPU::_C8()
{

}

void CPU::_C9()
{

}

void CPU::_CA()
{

}

void CPU::_CB()
{

}

void CPU::_CC()
{

}

void CPU::_CD()
{

}

void CPU::_CE()
{

}

void CPU::_CF()
{

}


// OPCODES DX
void CPU::_D0()
{

}

void CPU::_D1()
{

}

void CPU::_D2()
{

}

void CPU::_D3()
{

}

void CPU::_D4()
{

}

void CPU::_D5()
{

}

void CPU::_D6()
{

}

void CPU::_D7()
{

}

void CPU::_D8()
{

}

void CPU::_D9()
{

}

void CPU::_DA()
{

}

void CPU::_DB()
{

}

void CPU::_DC()
{

}

void CPU::_DD()
{

}

void CPU::_DE()
{

}

void CPU::_DF()
{

}


// OPCODES EX
void CPU::_E0()
{

}

void CPU::_E1()
{

}

void CPU::_E2()
{

}

void CPU::_E3()
{

}

void CPU::_E4()
{

}

void CPU::_E5()
{

}

void CPU::_E6()
{

}

void CPU::_E7()
{

}

void CPU::_E8()
{

}

void CPU::_E9()
{

}

void CPU::_EA()
{

}

void CPU::_EB()
{

}

void CPU::_EC()
{

}

void CPU::_ED()
{

}

void CPU::_EE()
{

}

void CPU::_EF()
{

}


// OPCODES FX
void CPU::_F0()
{

}

void CPU::_F1()
{

}

void CPU::_F2()
{

}

void CPU::_F3()
{

}

void CPU::_F4()
{

}

void CPU::_F5()
{

}

void CPU::_F6()
{

}

void CPU::_F7()
{

}

void CPU::_F8()
{

}

void CPU::_F9()
{

}

void CPU::_FA()
{

}

void CPU::_FB()
{

}

void CPU::_FC()
{

}

void CPU::_FD()
{

}

void CPU::_FE()
{

}

void CPU::_FF()
{

}


// OPCODES CB0X
void CPU::_CB00()
{

}

void CPU::_CB01()
{

}

void CPU::_CB02()
{

}

void CPU::_CB03()
{

}

void CPU::_CB04()
{

}

void CPU::_CB05()
{

}

void CPU::_CB06()
{

}

void CPU::_CB07()
{

}

void CPU::_CB08()
{

}

void CPU::_CB09()
{

}

void CPU::_CB0A()
{

}

void CPU::_CB0B()
{

}

void CPU::_CB0C()
{

}

void CPU::_CB0D()
{

}

void CPU::_CB0E()
{

}

void CPU::_CB0F()
{

}


// OPCODES CB1X
void CPU::_CB10()
{

}

void CPU::_CB11()
{

}

void CPU::_CB12()
{

}

void CPU::_CB13()
{

}

void CPU::_CB14()
{

}

void CPU::_CB15()
{

}

void CPU::_CB16()
{

}

void CPU::_CB17()
{

}

void CPU::_CB18()
{

}

void CPU::_CB19()
{

}

void CPU::_CB1A()
{

}

void CPU::_CB1B()
{

}

void CPU::_CB1C()
{

}

void CPU::_CB1D()
{

}

void CPU::_CB1E()
{

}

void CPU::_CB1F()
{

}


// OPCODES CB2X
void CPU::_CB20()
{

}

void CPU::_CB21()
{

}

void CPU::_CB22()
{

}

void CPU::_CB23()
{

}

void CPU::_CB24()
{

}

void CPU::_CB25()
{

}

void CPU::_CB26()
{

}

void CPU::_CB27()
{

}

void CPU::_CB28()
{

}

void CPU::_CB29()
{

}

void CPU::_CB2A()
{

}

void CPU::_CB2B()
{

}

void CPU::_CB2C()
{

}

void CPU::_CB2D()
{

}

void CPU::_CB2E()
{

}

void CPU::_CB2F()
{

}


// OPCODES CB3X
void CPU::_CB30()
{

}

void CPU::_CB31()
{

}

void CPU::_CB32()
{

}

void CPU::_CB33()
{

}

void CPU::_CB34()
{

}

void CPU::_CB35()
{

}

void CPU::_CB36()
{

}

void CPU::_CB37()
{

}

void CPU::_CB38()
{

}

void CPU::_CB39()
{

}

void CPU::_CB3A()
{

}

void CPU::_CB3B()
{

}

void CPU::_CB3C()
{

}

void CPU::_CB3D()
{

}

void CPU::_CB3E()
{

}

void CPU::_CB3F()
{

}


// OPCODES CB4X
void CPU::_CB40()
{

}

void CPU::_CB41()
{

}

void CPU::_CB42()
{

}

void CPU::_CB43()
{

}

void CPU::_CB44()
{

}

void CPU::_CB45()
{

}

void CPU::_CB46()
{

}

void CPU::_CB47()
{

}

void CPU::_CB48()
{

}

void CPU::_CB49()
{

}

void CPU::_CB4A()
{

}

void CPU::_CB4B()
{

}

void CPU::_CB4C()
{

}

void CPU::_CB4D()
{

}

void CPU::_CB4E()
{

}

void CPU::_CB4F()
{

}


// OPCODES CB5X
void CPU::_CB50()
{

}

void CPU::_CB51()
{

}

void CPU::_CB52()
{

}

void CPU::_CB53()
{

}

void CPU::_CB54()
{

}

void CPU::_CB55()
{

}

void CPU::_CB56()
{

}

void CPU::_CB57()
{

}

void CPU::_CB58()
{

}

void CPU::_CB59()
{

}

void CPU::_CB5A()
{

}

void CPU::_CB5B()
{

}

void CPU::_CB5C()
{

}

void CPU::_CB5D()
{

}

void CPU::_CB5E()
{

}

void CPU::_CB5F()
{

}


// OPCODES CB6X
void CPU::_CB60()
{

}

void CPU::_CB61()
{

}

void CPU::_CB62()
{

}

void CPU::_CB63()
{

}

void CPU::_CB64()
{

}

void CPU::_CB65()
{

}

void CPU::_CB66()
{

}

void CPU::_CB67()
{

}

void CPU::_CB68()
{

}

void CPU::_CB69()
{

}

void CPU::_CB6A()
{

}

void CPU::_CB6B()
{

}

void CPU::_CB6C()
{

}

void CPU::_CB6D()
{

}

void CPU::_CB6E()
{

}

void CPU::_CB6F()
{

}


// OPCODES CB7X
void CPU::_CB70()
{

}

void CPU::_CB71()
{

}

void CPU::_CB72()
{

}

void CPU::_CB73()
{

}

void CPU::_CB74()
{

}

void CPU::_CB75()
{

}

void CPU::_CB76()
{

}

void CPU::_CB77()
{

}

void CPU::_CB78()
{

}

void CPU::_CB79()
{

}

void CPU::_CB7A()
{

}

void CPU::_CB7B()
{

}

void CPU::_CB7C()
{

}

void CPU::_CB7D()
{

}

void CPU::_CB7E()
{

}

void CPU::_CB7F()
{

}


// OPCODES CB8X
void CPU::_CB80()
{

}

void CPU::_CB81()
{

}

void CPU::_CB82()
{

}

void CPU::_CB83()
{

}

void CPU::_CB84()
{

}

void CPU::_CB85()
{

}

void CPU::_CB86()
{

}

void CPU::_CB87()
{

}

void CPU::_CB88()
{

}

void CPU::_CB89()
{

}

void CPU::_CB8A()
{

}

void CPU::_CB8B()
{

}

void CPU::_CB8C()
{

}

void CPU::_CB8D()
{

}

void CPU::_CB8E()
{

}

void CPU::_CB8F()
{

}


// OPCODES CB9X
void CPU::_CB90()
{

}

void CPU::_CB91()
{

}

void CPU::_CB92()
{

}

void CPU::_CB93()
{

}

void CPU::_CB94()
{

}

void CPU::_CB95()
{

}

void CPU::_CB96()
{

}

void CPU::_CB97()
{

}

void CPU::_CB98()
{

}

void CPU::_CB99()
{

}

void CPU::_CB9A()
{

}

void CPU::_CB9B()
{

}

void CPU::_CB9C()
{

}

void CPU::_CB9D()
{

}

void CPU::_CB9E()
{

}

void CPU::_CB9F()
{

}


// OPCODES CBAX
void CPU::_CBA0()
{

}

void CPU::_CBA1()
{

}

void CPU::_CBA2()
{

}

void CPU::_CBA3()
{

}

void CPU::_CBA4()
{

}

void CPU::_CBA5()
{

}

void CPU::_CBA6()
{

}

void CPU::_CBA7()
{

}

void CPU::_CBA8()
{

}

void CPU::_CBA9()
{

}

void CPU::_CBAA()
{

}

void CPU::_CBAB()
{

}

void CPU::_CBAC()
{

}

void CPU::_CBAD()
{

}

void CPU::_CBAE()
{

}

void CPU::_CBAF()
{

}


// OPCODES CBBX
void CPU::_CBB0()
{

}

void CPU::_CBB1()
{

}

void CPU::_CBB2()
{

}

void CPU::_CBB3()
{

}

void CPU::_CBB4()
{

}

void CPU::_CBB5()
{

}

void CPU::_CBB6()
{

}

void CPU::_CBB7()
{

}

void CPU::_CBB8()
{

}

void CPU::_CBB9()
{

}

void CPU::_CBBA()
{

}

void CPU::_CBBB()
{

}

void CPU::_CBBC()
{

}

void CPU::_CBBD()
{

}

void CPU::_CBBE()
{

}

void CPU::_CBBF()
{

}


// OPCODES CBCX
void CPU::_CBC0()
{

}

void CPU::_CBC1()
{

}

void CPU::_CBC2()
{

}

void CPU::_CBC3()
{

}

void CPU::_CBC4()
{

}

void CPU::_CBC5()
{

}

void CPU::_CBC6()
{

}

void CPU::_CBC7()
{

}

void CPU::_CBC8()
{

}

void CPU::_CBC9()
{

}

void CPU::_CBCA()
{

}

void CPU::_CBCB()
{

}

void CPU::_CBCC()
{

}

void CPU::_CBCD()
{

}

void CPU::_CBCE()
{

}

void CPU::_CBCF()
{

}


// OPCODES CBDX
void CPU::_CBD0()
{

}

void CPU::_CBD1()
{

}

void CPU::_CBD2()
{

}

void CPU::_CBD3()
{

}

void CPU::_CBD4()
{

}

void CPU::_CBD5()
{

}

void CPU::_CBD6()
{

}

void CPU::_CBD7()
{

}

void CPU::_CBD8()
{

}

void CPU::_CBD9()
{

}

void CPU::_CBDA()
{

}

void CPU::_CBDB()
{

}

void CPU::_CBDC()
{

}

void CPU::_CBDD()
{

}

void CPU::_CBDE()
{

}

void CPU::_CBDF()
{

}


// OPCODES CBEX
void CPU::_CBE0()
{

}

void CPU::_CBE1()
{

}

void CPU::_CBE2()
{

}

void CPU::_CBE3()
{

}

void CPU::_CBE4()
{

}

void CPU::_CBE5()
{

}

void CPU::_CBE6()
{

}

void CPU::_CBE7()
{

}

void CPU::_CBE8()
{

}

void CPU::_CBE9()
{

}

void CPU::_CBEA()
{

}

void CPU::_CBEB()
{

}

void CPU::_CBEC()
{

}

void CPU::_CBED()
{

}

void CPU::_CBEE()
{

}

void CPU::_CBEF()
{

}


// OPCODES CBFX
void CPU::_CBF0()
{

}

void CPU::_CBF1()
{

}

void CPU::_CBF2()
{

}

void CPU::_CBF3()
{

}

void CPU::_CBF4()
{

}

void CPU::_CBF5()
{

}

void CPU::_CBF6()
{

}

void CPU::_CBF7()
{

}

void CPU::_CBF8()
{

}

void CPU::_CBF9()
{

}

void CPU::_CBFA()
{

}

void CPU::_CBFB()
{

}

void CPU::_CBFC()
{

}

void CPU::_CBFD()
{

}

void CPU::_CBFE()
{

}

void CPU::_CBFF()
{

}