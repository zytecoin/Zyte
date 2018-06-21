// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The zyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
 
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x0000029f6e74213c06065fe74f954e5e02263cdc3956d1f07ff5e71b72776516"))
		(5, uint256("0x000003ff161e9db0c0e9eb74d42c9beb32ad3ee6c40ff9a84ed3f52c68dd5966"))	
        (10, uint256("0x00000bd80a299af069a2d731e7771741fcd3007be8144400f4ee84949da74b6c"))
		(501, uint256("0x0000000000712c45d553044126d6bfabadb1ccfeb9f73ba2c430cff6291388fb"))	
        (2000, uint256("0x0000000000a5f0f299bd47f118c568d3b41e66e351bef43835bb3616946cfe3f"))
	;

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1529631412,// * UNIX timestamp of last checkpoint block
        2149,    // * total number of transactions between genesis and last checkpoint
        //   (the tx=... number in the SetBestChain debug.log lines)
        2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1518900000,
        0,
        250};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1518900000,
        0,
        100};
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xdc;
        pchMessageStart[1] = 0x2c;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xc1;
        vAlertPubKey = ParseHex("049df234dfde6f947218e44000a97be8df374bd41c5dd7475471bc29336e6af60891cd88a0e113400f5d3fbad55bf82e20425864f65a491aff000dc60e66c84684");
        nDefaultPort = 28676;
        bnProofOfWorkLimit = ~uint256(0) >> 20; 
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; 
        nTargetSpacingSlowLaunch = 3 * 60;  
        nTargetSpacing = 2* 60; 
        nLastPOWBlock = 26280000; 
        nRampToBlock = 500; 
        nMaturity = 10; 
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 42000000 * COIN; 

        const char* pszTimestamp = "Zyte the new cryptocurrency based in a Casino to add aditional value to the coin";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04192707a176ca5ca63378d21832bbd3c8cb46d9b0c90e837f6f5c42e92a82dbfcb2186091f62eb2d4c45463a988c78e21512902648d2228ec89a5d7fe0fa4db41") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1529094675;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1791817;


        hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear();
        vSeeds.clear();
        assert(hashGenesisBlock == uint256("0x0000029f6e74213c06065fe74f954e5e02263cdc3956d1f07ff5e71b72776516"));
        assert(genesis.hashMerkleRoot == uint256("0xdc7c6b99a2cd0c610852e3c2e540f2d3e0b3ed796df61bae996cc39801b38af7"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); 
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 29);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 126);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x4C)(0x21)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x33)(0x2D)(0x2B).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is 'TBD'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x89)(0x00).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
		vSeeds.push_back(CDNSSeedData("207.246.119.170", "207.246.119.170"));   
		vSeeds.push_back(CDNSSeedData("199.247.10.251", "199.247.10.251"));    
		vSeeds.push_back(CDNSSeedData("108.61.212.106", "108.61.212.106")); 
		vSeeds.push_back(CDNSSeedData("149.28.97.164", "149.28.97.164"));  

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04d90ac38f2ba9e65968193b1e32e5260e8bf3d0d71dd69d24563a778f27d716ef2c4e0cd796d483ce0209906130cc380f9b5ac790d15103539a30af33ae6d7892";
        strObfuscationPoolDummyAddress = "P6xToMedbmhz4LdbgjaRZ5QCNYpityBznh";
        nStartMasternodePayments = 1519260063;
    }


    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0xa0;

        vAlertPubKey = ParseHex("048ea26bc698946b3f4193aef683b6760bd132e309381425e651be31215bcfc2dad7f9146fb700c2d103e621fbc253169563af35c67b9258c4bd2f2a76cf1a1fa3");
        nDefaultPort = 43246;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 120; // 120 Seconds
        nTargetSpacing = 5 * 120;  // 600 Seconds
        nLastPOWBlock = 1000;
        nMaturity = 15;
        nMaxMoneyOut = 33284220 * COIN; // 2050 Maximum

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1518900000;
        genesis.nNonce = 746269;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();

        hashGenesisBlock == uint256("0x");
        genesis.hashMerkleRoot == uint256("0x");
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("zyte.io", "test01.zyte.io"));
        vSeeds.push_back(CDNSSeedData("zyte.io", "test02.zyte.io"));
        vSeeds.push_back(CDNSSeedData("zyte.io", "test03.zyte.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // Testnet zyte addresses start with 'T'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);  // Testnet zyte script addresses start with '5' or '6'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet zyte BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet zyte BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet zyte BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "04a72cdafbd514beba17787899e4f97346fcf96575cc74d545145f9056d09c39492d8ddf42971bd5a3ac03947d40d7470bc0b3000fab52ebb6ca2c509a404ce324";
        strObfuscationPoolDummyAddress = "TUQ57Fbh1crybrDhV6X9SDH95H4oSq4v6p";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // zyte: 1 day
        nTargetSpacing = 1 * 60;        // zyte: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 52589;
//        assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;
/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 52591;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;
CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}
const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}
void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
