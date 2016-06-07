#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <utility>
#include <TNtuple.h>

using namespace std;

class Ntuplizer : public edm::EDAnalyzer {
  public:
    /// Constructor
    explicit Ntuplizer(const edm::ParameterSet&);
    /// Destructor
    virtual ~Ntuplizer();  
    
  private:
  //----edm control---
    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;
    void Initialize(); 
    
    TTree *_tree;
    std::string _treeName;
    // -------------------------------------
    // variables to be filled in output tree
    ULong64_t       _indexevents;
    Int_t           _runNumber;
    Int_t           _lumi;
};


// ----Constructor and Destructor -----
Ntuplizer::Ntuplizer(const edm::ParameterSet& pset) : 
{
    this -> _treeName = pset.getParameter<string>("treeName");
    this -> Initialize();
    return;
}
