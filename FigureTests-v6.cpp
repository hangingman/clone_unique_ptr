#include <gmock/gmock.h>
#include <type_traits>
#include <functional>
#include <memory>

namespace v5 {

  // bnfc AST spec
  // (1) Node has one abstract class
  // (1-a) abstract class implements Visitable
  //
  // (2) Node has several implement classes
  // (2-a) implement classes have child elements as field
  // (2-b) implement classes have following methods:
  // * Copy ctor, assign(=)
  // * Constructor with child elements
  // * Dtor
  // * virtual methods of accept, clone
  // * swap

  // -- bnfc sample start
  class Exp;
  class Factor;
  class ImmExp;
  class IdentFactor;
  typedef std::string Ident;

  class Visitor
  {
  public:
    virtual ~Visitor() {}
  };

  class Visitable
  {
  public:
    virtual ~Visitable() {}
    virtual void accept(Visitor *v) = 0;
  };

  // bnfc AST
  class Exp : public Visitable
  {
  public:
    virtual Exp *clone() const = 0;
  };

  class Factor : public Visitable
  {
  public:
    virtual Factor *clone() const = 0;
  };

  class ImmExp : public Exp
  {
  public:
    std::unique_ptr<Factor> factor_;

    // https://stackoverflow.com/a/16030243/2565527
    ImmExp(ImmExp && other) : factor_(std::move(other.factor_)) {}
    ImmExp &operator=(ImmExp && other) { factor_ = std::move(other.factor_);return *this; }
    ImmExp(std::unique_ptr<Factor> p1) { factor_ = std::move(p1); }

    ~ImmExp() {}
    virtual void accept(Visitor *v) {}
    virtual ImmExp *clone() const {}
    void swap(ImmExp & other)  { std::swap(factor_, other.factor_); };
  };

  class IdentFactor : public Factor
  {
  public:
    std::unique_ptr<Ident> ident_;

    IdentFactor(IdentFactor && other) : ident_(std::move(other.ident_)) {}
    IdentFactor &operator=(IdentFactor && other) { ident_ = std::move(other.ident_);return *this; };
    IdentFactor(std::unique_ptr<Ident> p1) { ident_ = std::move(p1); }
    ~IdentFactor() {}
    virtual void accept(Visitor *v) {}
    virtual IdentFactor *clone() const {};
    void swap(IdentFactor & other) { std::swap(ident_, other.ident_); };
  };
  // bnfc sample end --/


using namespace ::testing;

TEST(FigureTests_v6, simple_instance_and_clone)
{
  auto id = std::make_unique<Ident>("Hello");
  auto factor = std::make_unique<IdentFactor>(std::move(id));
  auto immExp = std::make_unique<ImmExp>(std::move(factor));
}

} // v6 namespace
