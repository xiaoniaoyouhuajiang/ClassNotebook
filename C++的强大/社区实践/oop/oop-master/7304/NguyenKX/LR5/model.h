
#ifndef MODEL_H
#define MODEL_H
#include <type_traits>
#include "basehandler.h"
#include "ihandler.h"
#include "myexception.h"
#include "coordinate.h"
#include "reader.h"
#include "writer.h"
#include "handlerregistry.h"
template <typename T, typename U>
class Model : public IMultiInputHandler<T>, public BaseHandler <T,U>{
protected:
    std::vector<std::shared_ptr<Unit>> handlers;
    IHandler<T> *inputHandler;
    HandlerOutput<U> *outputHandler;

    std::map<std::size_t, std::vector<Memento*>> history;
public:
    using IMultiInputHandler<T>::handle;
    Model() : BaseHandler<T,U>(), inputHandler(nullptr), outputHandler(nullptr){
        this->isOutput = true;
    }

    std::shared_ptr<Unit> add(Unit *h){
        std::shared_ptr<Unit> sp (h);
        handlers.push_back(sp);
        return sp;
    }

    void remove(Unit* h){
        std::size_t target_index = 99999;
        for(std::size_t i = 0; i< handlers.size();i++){
            if(h->id==handlers[i]->id) target_index = i;
            for(std::size_t slot = 0;slot<handlers[i]->noOut;slot++){
                if(handlers[i]->getNextU(slot)!=nullptr && handlers[i]->getNextU(slot)->id==h->id){
                    handlers[i]->setNext(slot,nullptr);
                }
            }
        }
        if(dynamic_cast<Unit*>(inputHandler)!=nullptr && dynamic_cast<Unit*>(inputHandler)->id==h->id){
            this->setInput();
        }
        if(dynamic_cast<Unit*>(outputHandler)!=nullptr && dynamic_cast<Unit*>(outputHandler)->id==h->id){
            this->setOutput();
        }
        if(target_index<handlers.size())
            handlers.erase(handlers.begin()+target_index);

    }

    bool contains(Unit *unit){
        bool isManaged = false;
        for(const auto &h : handlers){
            if(h.get()->id==unit->id){
                isManaged = true;
                break;
            }
        }
        return isManaged;
    }

    std::vector<std::shared_ptr<Unit>> getManagedHandlers(){
        return handlers;
    }
    //template <typename X>

    void setInput(Unit *handler=nullptr){
        if(handler==nullptr){
            this->inputHandler = nullptr;
            this->noInp = 0;
            return;
        }
        IHandler<T> *conv = dynamic_cast<IHandler<T>*>(handler);
        if(conv!=nullptr)
            setInput(conv);
        else throw TypeException();
    }

    void setOutput(Unit *handler=nullptr){
        if(handler==nullptr){
            this->outputHandler = nullptr;
            this->noOut = 0;
            return;
        }
        HandlerOutput<U> *conv = dynamic_cast<HandlerOutput<U>*>(handler);
        if(conv!=nullptr)
            setOutput(conv);
        else throw TypeException();
    }

    void setInput(IHandler<T> *handler){
        //check if h is in handlers
        if(this->contains(dynamic_cast<Unit*>(handler))){
            inputHandler = handler;
            this->noInp = dynamic_cast<Unit*>(handler)->noInp;
            // log about success
        }else{
            // log about failure
        }
    }

    //template <typename X>
    void setOutput(HandlerOutput<U> *handler){
        // check if r is in handlers
        if(this->contains(dynamic_cast<Unit*>(handler))){
            outputHandler = handler;
            dynamic_cast<Unit*>(handler)->isOutput = true;

            this->noOut = dynamic_cast<Unit*>(handler)->noOut;
            this->nexts.reset(new IHandler<U>*[this->noOut]);
        }
    }
    template <typename X, typename Y>
    void replace(Unit* h1, Unit *h2){
        BaseHandler<X,Y>* bh1 = dynamic_cast<BaseHandler<X,Y>*>(h1);
        BaseHandler<X,Y>* bh2 = dynamic_cast<BaseHandler<X,Y>*>(h2);
        if(bh1==nullptr||bh2==nullptr) throw TypeException();
        replace(bh1,bh2);
    }
    template <typename X, typename Y>
    void replace(BaseHandler<X,Y> *h1, BaseHandler<X,Y> *h2){
        if(h1->noInp!=h2->noInp) throw HandlerStructureException();
        if(h1->noOut!=h2->noOut) throw HandlerStructureException();
        if(h1->id==h2->id) return;
        if(!this->contains(h1)||!this->contains(h2)) return;
        for(std::shared_ptr<Unit> &h : handlers){
            HandlerOutput<X>* h_out = dynamic_cast<HandlerOutput<X>*>(h.get());
            if(h_out!=nullptr){
                for(std::size_t i = 0; i<h->noOut;i++){
                    if(h_out->getNext(i)!=nullptr){
                        if(h_out->getNext(i)==h1){
                            h_out->setNext(i,dynamic_cast<IHandler<X>*>(h2));
                        }
                    }
                }
            }
        }
        if(this->outputHandler!=nullptr&&this->outputHandler==dynamic_cast<HandlerOutput<U>*>(h1)) {
            this->outputHandler = dynamic_cast<HandlerOutput<U>*>(h2);
            h2->isOutput = true;
        }
        else{
            h2->isOutput = h1->isOutput;
            h1->isOutput = true; // set to true to pass the verify test
            for(std::size_t i = 0;i<h1->noOut;i++){
                h2->setNext(i,h1->getNext(i));
                h1->setNext(i);
            }

        }

        if(dynamic_cast<Unit*>(this->inputHandler)->id==h1->id){
            this->inputHandler = dynamic_cast<IHandler<T>*>(h2);
        }

    }

    void backup(){
        for(const auto &h :handlers){
            IBackupable *target = dynamic_cast<IBackupable*>(h.get());
            if(target!=nullptr){
                Memento *m = target->makeBackup();
                history[h->id].push_back(m);
            }
        }
    }

    void undo(){
        for(const auto &h :handlers){
            IBackupable *target = dynamic_cast<IBackupable*>(h.get());
            if(history.find(h->id)!=history.end()){
                if(!history[h->id].empty()){
                    Memento *m = history[h->id].back();
                    target->restore(m);
                    history[h->id].pop_back();
                }
            }
        }

    }

    virtual bool verify() const{
        if(inputHandler==nullptr || this->noOut==0 || this->noInp == 0) return false;
        else{
            return  dynamic_cast<Unit*>(inputHandler)->verify() && BaseHandler<T,U>::verify();
        }
    }
    virtual void handle(T inp){
        if(this->verify()){
            if(inputHandler!=nullptr)
            {
                inputHandler->handle(inp);
                // TODO: forward all results to nexts
                if(!this->isOutput){
                    for(std::size_t i = 0; i<this->noOut;i++){
                        this->nexts[i]->handle(outputHandler->getResult()[i]);
                    }
                }
            }
        }

    }

    virtual U* getResult() const {
        return outputHandler->getResult();
    }

    friend std::ostream & operator << (std::ostream &out, const Model &h){
        out<< "Model (id="<<h.id<<") ("<<(h.verify()?"valid":"invalid")<<"): ";
        for(std::size_t i = 0; i<h.noOut; i++){
            out<<h.getResult()[i]<<" ";
        }
        return out<<std::endl;
    }

    void clearStructure(){
        handlers.clear();
        setInput();
        setOutput();
    }

    template <typename R ,typename = typename std::enable_if<std::is_base_of<IReader, R>::value, R>::type>
    void loadFromFile(std::string fileName){
        R reader(fileName);
        // clear current model
        this->clearStructure();

        // read number of handlers in management
        std::size_t n=0;
        reader>>n;
        for(std::size_t i = 0; i<n;i++){
            // create handlers (using typeId and id)
            std::size_t typeId=0, id=0;
            reader>>typeId;
            reader>>id;
            auto unit = this->add(HandlerRegistry::getInstance().getByTypeId(typeId));
            reader>>unit.get();
            unit->id = id;
        }

        // load idSerial;
        reader>>Unit::idSerial;

        // load connection;
        for(std::size_t i = 0; i<n;i++){
            std::size_t sourceId, len;
            reader>>sourceId;
            reader>>len;
            for(std::size_t j = 0;j<len;j++){
                std::size_t destId;
                reader>>destId;
                if(destId!=99999)
                    this->connectById(sourceId,j,destId);
            }
        }
        // load input and output nodes
        {
            std::size_t id;
            reader>>id;
            if(id!=99999)
                this->setInput(this->getHandlerById(id));
            reader>>id;
            if(id!=99999)
                this->setOutput(this->getHandlerById(id));

        }

    }

    template <typename R ,typename = typename std::enable_if<std::is_base_of<IWriter, R>::value, R>::type>
    void saveToFile(std::string fileName){
        R writer(fileName);

        // write number of handlesr in management
        writer<<this->handlers.size();

        for(std::shared_ptr<Unit> &handler : this->handlers){
            // save typeId and Id
            writer<<handler->type<<handler->id;
            writer<<handler.get();
        }
        // save idSerial
        writer<<Unit::idSerial;

        // write connections
        for(std::shared_ptr<Unit> &handler : this->handlers){
            writer<<handler->id;
            writer<<handler->getNexts().size();
            for(std::size_t i = 0;i<handler->getNexts().size();i++){
                writer<<handler->getNexts()[i];
            }
        }

        // write input and output nodes
        if(inputHandler==nullptr){
            writer<<99999;
        }else {
            writer<<(dynamic_cast<Unit*>(inputHandler)->id);
        }

        if(outputHandler==nullptr){
            writer<<99999;
        }else {
            writer<<(dynamic_cast<Unit*>(outputHandler)->id);
        }

    }


    Unit* getHandlerById(std::size_t id){
        Unit* unit = nullptr;
        for(std::shared_ptr<Unit> &u : this->getManagedHandlers()){
            if(u->id==id) unit = u.get();
        }
        if(unit!=nullptr) return unit;
        else throw HandlerNotFoundException();

    }

    void connectById(std::size_t id1, std::size_t slot, std::size_t id2){
        Unit* unit1 = getHandlerById(id1);
        Unit* unit2 = getHandlerById(id2);
        unit1->setNext(slot,unit2);
    }


    std::vector<std::size_t> getUnitIds(){
        std::vector<std::size_t> ids;
        for(std::shared_ptr<Unit> &h : this->getManagedHandlers()){
                ids.push_back(h->id);
        }
        return std::vector<std::size_t>(ids);
    }

    std::vector<std::pair<std::size_t,std::size_t>> getConnections()
    {
        std::vector<std::pair<std::size_t,std::size_t>> connections;
        for(std::shared_ptr<Unit> &h : this->getManagedHandlers()){
            for(auto &nxt : h->getNexts()){
                if(nxt!=99999)
                    connections.push_back(std::pair<std::size_t,std::size_t>(h->id,nxt));
            }
        }
        return std::vector<std::pair<std::size_t,std::size_t>>(connections);

    }

    virtual std::string toString(){
        std::stringstream ss;
        ss<<"Id: "<<this->id<<"\t\t";
        ss<<"Num. input:  "<<this->noInp<<"\t\t";
        ss<<"Num. output: "<<this->noOut<<std::endl;
        ss<<"\t\t"<<"Status: "<<(this->verify()?"valid":"invalid")<<std::endl;
        if(this->outputHandler!=nullptr){
            ss<<"\t\t"<<"State: ";
            for(std::size_t i = 0;i<this->noOut;i++){
                U u = this->getResult()[i];
                ss<<"\t"<<u;
            }
        }
        std::size_t idInp = this->inputHandler==nullptr?99999:dynamic_cast<Unit*>(this->inputHandler)->id;

        std::size_t idOut= this->outputHandler==nullptr?99999:dynamic_cast<Unit*>(this->outputHandler)->id;

        ss<<"\n\t\t";
        if(idInp==99999)
            ss<<"Input handler: "<< "not set";
        else
            ss<<"Input handler: "<< idInp;
        ss<<"\t\t";
        if(idOut==99999)
            ss<<"Output handler: "<< "not set";
        else
            ss<<"Output handler: "<< idOut;
        ss<<std::endl;

        return ss.str();
    }
    virtual Unit* clone(){
        return new Model;
    }
private:
    virtual void process(std::size_t, const T*, std::size_t , U *){}
};




#endif // MODEL_H
