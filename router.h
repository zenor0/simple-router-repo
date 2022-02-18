#include <fstream>
#include <iostream>
#include "cmdline.h"


// TO-DO
// Use a funciton to unite different algorithm models.

extern bool DEBUG_STATUS;
extern bool INFO_STATUS;
extern cmdline::parser cmdParser;

using std::string;
using std::cin, std::cout, std::endl;

#ifndef ENUM______

// Use different bits to distinct algorithms.

enum ALGORITHM_SIGNS
{
	naive		= 1 << 0,
	hicuts		= 1 << 1,
	hypercuts	= 1 << 2,
};

enum dimension
{
	sourIP		= 1 << 0,
	destIP		= 1 << 1,
	sourPort	= 1 << 2,
	destPort	= 1 << 3,
	protocol	= 1 << 4,
};

#endif


#ifndef CORESTR___
#define CORESTR___

// Definations of basic data structures

// Ranges - store the informations of left and right values
class RANGE
{
public:
	unsigned int start;
	unsigned int end;

	unsigned int length() {return end - start + 1;};
	RANGE &ApplyMask(const string &ip, int maskBit);
	bool isVaild(unsigned int var) {return (var >= start && var <= end);};
	bool isVaild(RANGE &var) {return (var.start >= start && var.end <= end);};
};

class PROTRANGE : public RANGE
{
public:
	PROTRANGE() = default;
	PROTRANGE &init(const string &str) {sscanf(str.c_str(), "%x/%x", &start, &end);	return *this;};
	bool isVaild(PROTRANGE &var) {return (var.start >= start && var.end <= end);};

	bool isVaild(unsigned int var)
	{
		if (end == 0xFF)
			return var == start;
		if (end == 0x00)
			return true;
		return RANGE::isVaild(var);
	}
};


// Data structure

class DATAItem
{
public:
	int result = -1;

	unsigned int sourIP;
	unsigned int destIP;
	unsigned int sourPort;
	unsigned int destPort;
	unsigned int proto;

	DATAItem &read(const string rawDataString);
	std::ostream &print(std::ostream &os);
	unsigned int DimCast(unsigned dim)
	{
		switch (dim)
		{
			case dimension::sourIP:
				return sourIP;
			case dimension::destIP:
				return destIP;
			case dimension::sourPort:
				return sourPort;
			case dimension::destPort:
				return destPort;
			case dimension::protocol:
				return proto;
			default:
			// Throw a error
				cout << "cast error" << endl;
				return sourIP;
		}
	};
};


// Rule structure

class RULEItem
{
public:
	unsigned int classID;

	RANGE sourIP;
	RANGE destIP;
	RANGE sourPort;
	RANGE destPort;
	PROTRANGE proto;

	RULEItem &read(const string rawRuleString);
	std::ostream &print(std::ostream &os);
	RANGE &DimCast(unsigned dim)
	{
		switch (dim)
		{
			case dimension::sourIP:
				return sourIP;
			case dimension::destIP:
				return destIP;
			case dimension::sourPort:
				return sourPort;
			case dimension::destPort:
				return destPort;
			case dimension::protocol:
				return proto;
			default:
			// Throw a error
				cout << "cast error" << endl;
				return sourIP;
		}
	};
	bool isValid(DATAItem &packet) {return (sourIP.isVaild(packet.sourIP) && destIP.isVaild(packet.destIP) && sourPort.isVaild(packet.sourPort) &&
											destPort.isVaild(packet.destPort) && proto.isVaild(packet.proto));};
	bool isValid(RULEItem &packet) {return (sourIP.isVaild(packet.sourIP) && destIP.isVaild(packet.destIP) && sourPort.isVaild(packet.sourPort) &&
											destPort.isVaild(packet.destPort) && proto.isVaild(packet.proto));};

};

#endif

#ifndef CORECLA___
#define CORECLA___


class base_router
{
public:
	typedef struct RnodeNaive
	{
		RULEItem item;
		struct RnodeNaive *next;

	} RuleNodeBase;

	base_router() = default;
	base_router(string rule, string data, string output) : ruleFileName(rule), dataFileName(data), outputFileName(output) {};

	// TO-DO
	base_router &Init(string rule, string data, string output);
	int Match(void);
	int add(RuleNodeBase &newNode);

	// Basic info functions
	double time() {return (1.0 * matchEndTime - matchStartTime) / CLOCKS_PER_SEC;};	// Secs
	int rulenum() {return nodeCount;};
	long long memory() {return (nodeCount * sizeof(RuleNodeBase));};	// Bytes

private:

protected:
	string routerType = "naive";
	RuleNodeBase *rootMap = nullptr;

	string ruleFileName = "rule";
	string dataFileName = "packet";
	string outputFileName = "out";

	std::ofstream outputStream;
	std::ofstream logStream;

	unsigned int nodeCount = 0;
	unsigned int matchStartTime = 0;
	unsigned int matchEndTime = 0;

	int ReadRuleMap(const string &ruleFileName);
	bool LinearSearch(DATAItem &packet);

};

// Hicuts
class hicuts_router : public base_router
{
public:
	hicuts_router() = default;
	hicuts_router(unsigned int binth, unsigned int spFac) : binth(binth), spFac(spFac) {};

	class RboxHicuts
	{
	public:
		RULEItem nodeRange;		// decide by upper node
								// define this node's Range
		int cutDimension;		// dynamic
		unsigned int np = 2;	// np(short for Number of Partitions), must be multiples of 2

		std::vector<RboxHicuts *> next;	//divided by cutDimension, cutCount partitions in total.

		// Leaf infos
		bool isLeaf = false;		// this may be useless
		std::vector<RULEItem *> ruleValid;

		// Functions
		bool LinearSearch(DATAItem &packet);
		unsigned int GetRuleNum(RuleNodeBase & ruleMap);
		unsigned int GetRuleNumSumInNP(RuleNodeBase &ruleMap, unsigned int np, unsigned int dim);
		RboxHicuts *GetNext(DATAItem &packet);
		RboxHicuts &SetNP(unsigned int var) {np = var; return *this;};
		RboxHicuts &SetLeaf(RuleNodeBase &ruleMap);
		RboxHicuts &SetDimension(RuleNodeBase &ruleMap);
		RboxHicuts &CutBox(unsigned int np, unsigned int dim);
		
	private:
	
	};


	hicuts_router &Init();
	int BuildTree(RboxHicuts &box);
	int Match();
	int Pruning();	// optimize tree performance

	// TO-DO
	// Update();
	// del();
private:
	string router_type = "Hicuts";
	RboxHicuts *rootNode = nullptr;

	unsigned int binth = 8;
	unsigned int spFac = 4;


protected:
	inline unsigned int spmf(unsigned int n) {return spFac * n;};
	unsigned int GetNP(RboxHicuts &box);


};


#endif


// HicutsTree Construction Pseudocode

// Necessary structures

	// Base node - store incomplete node(parent node)(big big BOX)
		// Point to leafnode
		// maybe array or hash function?? which is better?
		
		// k-dimension field		B(v)
		// dimension to be cut		dim(C(v))
		// number of patitions		np(C(v))

	// Leaf Node - store rules whose amount belows binth(bin-threshold) (child node)
		// store rule's classID

// Key parameter (define by users, or decided by rule map?)
	// binth - bin-threshold
	// spfac - space factor

// notice
	// Reduce the dimension as more as possible!
	// Let np() be 2's power number / even number


// Using recusion to build tree!
// Build function - build(Box(root)) <receiving the box>

	// Read rules as linear list first? to get the main BOX(rule map)

	// Exit recursion conditions
		// Check if cut's rules <= binth
			// Let it be a leaf
			// End building, return
		// else
			// still build

	// Decide cut from which dimension

	// Cut the box

		// Space measure function decide number of partitions	spmf()

		// Then cut it!

		// For loop the cut(v), 
			// Recusion, Build them again
			// Check moudle at the very beginning will decide whether to go on.



// Check ruleNum moudle
	// Treverse the whole rule map
	// Count valid rules

// spmf() so mystrery = =
	// spmf(N) = spfac * N

// spaceMeasure(C(v)) = numRulesSum(child node) + numberOfPartition(C(v))
