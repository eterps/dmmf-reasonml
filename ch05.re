open Js;
type undefined = exn;

type result('success, 'failure) =
  | Ok('success)
  | Error('failure);

// === Modeling Simple Values ===

type customerId =
  | CustomerId(int);

type customerId2 = CustomerId(int);

type widgetCode = WidgetCode(string);
type unitQuantity = UnitQuantity(int);
type kilogramQuantity = KilogramQuantity(float);

// === Working with Single Case Unions ===

let customerId = CustomerId(42);

let CustomerId(innerValue) = customerId;
log(innerValue);

let processCustomerId = (CustomerId(innerValue)) => {
  log({j|innerValue is $innerValue|j})
};
processCustomerId(customerId);

// === Avoiding Performance Issues with Simple Types

type unitQuantity3 = int;
// No translation yet for [<Struct>]
// No translation yet for UnitQuantities of int[]

// === Modeling Complex Data / Modeling Unknown Types ===

type customerInfo = undefined;
type shippingAddress = undefined;
type billingAddress = undefined;
type orderLine = {id: int, price: int};
type billingAmount = undefined;

type order = {
  customerInfo: customerInfo,
  shippingAddress: shippingAddress,
  billingAddress: billingAddress,
  orderLines: list(orderLine),
  amountToBill: billingAmount
};

// === Modeling with Choice Types ===

type gizmoCode = undefined;

type productCode =
  | Widget(widgetCode)
  | Gizmo(gizmoCode);

type orderQuantity =
  | Unit(unitQuantity)
  | Kilogram(kilogramQuantity);

// === Modeling Workflows with Functions ===

type unvalidatedOrder = undefined;
type validatedOrder = undefined;

type validateOrder = (unvalidatedOrder) => validatedOrder;

// === Working with Complex Inputs and Outputs ===

type acknowledgementSent = undefined;
type orderPlaced = undefined;
type billableOrderPlaced = undefined;

type placeOrderEvents = {
  acknowledgementSent: acknowledgementSent,
  orderPlaced: orderPlaced,
  billableOrderPlaced: billableOrderPlaced
};

type placeOrder = (unvalidatedOrder) => placeOrderEvents;

type quoteForm = undefined;
type orderForm = undefined;
type envelopeContents = EnvelopeContents(string);
type categorizedMail =
  | Quote(quoteForm)
  | Order(orderForm);

type categorizeInboundMail = (envelopeContents) => categorizedMail;

type productCatalog = undefined;
type pricedOrder = undefined;
type calculatePrices = (orderForm, productCatalog) => pricedOrder;

type calculatePricesInput = {
  orderForm: orderForm,
  productCatalog: productCatalog
};
type calculatePrices2 = (calculatePricesInput) => pricedOrder;

// === Documenting Effects in the Function Signature ===

type validateOrder2 = (unvalidatedOrder) => result(validatedOrder, list(validationError))
and validationError = {
  fieldName: string,
  errorDescription: string
};

// No solution yet for Async

type validationResponse('a) = result('a, list(validationError));

type validateOrder3 = (unvalidatedOrder) => validationResponse(validatedOrder);

// === A Question of Identity: Value Objects ===

let widgetCode1 = WidgetCode("W1234");
let widgetCode2 = WidgetCode("W1234");
log(widgetCode1 == widgetCode2); // prints "true"

type name = {firstName: string, lastName: string};

let name1 = {firstName: "Alex", lastName: "Adams"};
let name2 = {firstName: "Alex", lastName: "Adams"};
log(name1 == name2) // prints "true"

// etc.

// === A Question of Identity: Entities ===

type contactId = ContactId(int);
type contact = {
  contactId: contactId,
  phoneNumber: undefined,
  emailAddress: undefined
};

// === Adding Identifiers to Data Definitions ===

// The outside approach (less common):

type unpaidInvoiceInfo = undefined;
type paidInvoiceInfo = undefined;
type invoiceInfo =
  | Unpaid(unpaidInvoiceInfo)
  | Paid(paidInvoiceInfo);
type invoiceId = int;
type invoice = {
  invoiceId: invoiceId, // "outside" the two child cases
  invoiceInfo: invoiceInfo
};

// The inside approach (more common):

type unpaidInvoice = {
  invoiceId: invoiceId // id stored "inside"
};
type paidInvoice = {
  invoiceId: invoiceId // id stored "inside"
};
type invoice2 =
  | Unpaid(unpaidInvoice)
  | Paid(paidInvoice);

let invoice = Paid({invoiceId: 42});
switch(invoice) {
  | Unpaid(id) => log({j|The unpaid invoiceId is $id|j})
  | Paid(id) => log({j|The paid invoiceId is $id|j})
};

// === Implementing Equality for Entities ===

type contactId2 = int;
type phoneNumber = int;
type emailAddress = string;

type contact2 = {
  contactId: contactId2,
  phoneNumber: phoneNumber,
  emailAddress: emailAddress
};
let c1 = {contactId: 42, phoneNumber: 949121, emailAddress: "info@test.org"};
let c2 = {contactId: 42, phoneNumber: 949121, emailAddress: "info@test.org"};

log(c1 == c2); // Wrong! Need to find a solution yet

// === Immutability and Identity ===
 
type personId = PersonId(int);
type person = {personId: personId, name: string};

let initialPerson = {personId: PersonId(42), name: "Joseph"};
let updatedPerson = {...initialPerson, name: "Joe"};
log(updatedPerson);

type updateName = (person, name) => person;

// === Aggregates ===

/*
let changeOrderLinePrice = (order, orderLineId, newPrice) => {
  let orderLine = order.orderLines |> findOrderLine(orderLineId);
  let newOrderLine = {...orderLine, price: newPrice};
  let newOrderLines =
    order.orderLines |> replaceOrderLine(orderLineId, newOrderLine);
  let newOrder = {...order, orderLines: newOrderLines};
  newOrder;
};
*/
