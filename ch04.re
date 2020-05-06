open Js;

// === 4. Type Signatures ===

// int -> int
let add1 = (x) => x + 1;
add1(3) |> log;

// int -> int -> int or (int, int) -> int
let add = (x, y) => x + y;
add(3, 2) |> log;

let squarePlusOne = (x) => {
  let square = x * x;
  square + 1;
}
squarePlusOne(3) |> log;

// === 4. Functions with Generic Types ===

// ('a, 'a) -> bool
let areEqual = (x, y) => x == y;
areEqual(2, 2) |> log;

// === 4. "AND" Types ===

type appleVariety = GoldenDelicious | GrannySmith | Fuji;
type bananaVariety = Cavendish | GrosMichel | Manzano;
type cherryVariety = Montmorency | Bing;

type fruitSalad = {
  apple: appleVariety,
  banana: bananaVariety,
  cherries: cherryVariety
};

// === 4. "OR" Types ===

type fruitSnack =
  | Apple(appleVariety)
  | Banana(bananaVariety)
  | Cherries(cherryVariety);

// a fruitSnack is either an appleVariety (tagged with Apple) or a bananaVariety (tagged with Banana) etc.

// === 4. Simple Types ===

type productCode =
  | ProductCode(string);

type productCode2 = ProductCode(string);

// === 4. Working with Types ===

type person = {first: string, last: string};

let aPerson = {first: "Alex", last: "Adams"};

let {first: first, last: last} = aPerson;
log((first, last));

let first = aPerson.first;
let last = aPerson.last;
log((first, last));

type orderQuantity =
  | UnitQuantity(int)
  | KilogramQuantity(float);

let anOrderQtyInUnits = UnitQuantity(10);
let anOrderQtyInKg = KilogramQuantity(2.5);

// UnitQuantity & KilogramQuantity are not types, just distinct cases of the orderQuantity type

let printQuantity = (aOrderQty) => {
  switch(aOrderQty) {
  | UnitQuantity(uQty) => {j|$uQty units|j}
  | KilogramQuantity(kgQty) => {j|$kgQty kg|j}
  }
};

printQuantity(anOrderQtyInKg) |> log;

// === 4. Building a Domain Model by Composing Types ===

type checkNumber = CheckNumber(int);
type cardNumber = CardNumber(string);

type cardType = Visa | Mastercard;

type creditCardInfo = {
  cardType: cardType,
  cardNumber: cardNumber
};

type paymentMethod =
  | Cash
  | Check(checkNumber)
  | Card(creditCardInfo);

type paymentAmount = PaymentAmount(float);
type currency = EUR | USD;

type payment = {
  amount: paymentAmount,
  currency: currency,
  method: paymentMethod
};

type unpaidInvoice = UnpaidInvoice;
type paidInvoice = PaidInvoice;
type payInvoice = (unpaidInvoice, payment) => paidInvoice;

type convertPaymentCurrency = (payment, currency) => payment;

// === 4. Modeling Optional Values ===

type personalName = {
  firstName: string,
  middleInitial: option(string),
  lastName: string
};

// === 4. Modeling errors ===

type result('success, 'failure) =
  | Ok('success)
  | Error('failure);

type paymentError =
  | CardTypeNotRecognized
  | PaymentRejected
  | PaymentProviderOffline;

type payInvoice2 = (unpaidInvoice, payInvoice) => result(paidInvoice, paymentError);

// === 4. Modeling No Value at All ===

type customer = int;
type saveCustomer = customer => unit;
type nextRandon = unit => int;

// === 4. Modeling Lists and Collections ===

type orderId = int;
type orderLine = unit;
type order = {
  orderId: orderId,
  lines: list(orderLine)
};

let aList = [1, 2, 3];

let aNewList = [0, ...aList];

let printList1 = (aList) => {
  switch(aList) {
  | [] => log("list is empty")
  | [x] => log({j|list has one element: $x|j})
  | [x, y] => log({j|list has two elements: $x and $y|j})
  | _ => log("list has more than two elements")
  };
};

printList1([4, 5]);

let printList2 = (aList) => {
  switch(aList) {
  | [] => log("list is emptry")
  | [first, ..._] => log({j|list is non-empty with the first element being: $first|j})
  };
};

printList2([3]);

// === 4. Organizing Types in Files and Projects ===

module Payments = {
  type checkNumber = CheckNumber(int);

  type paymentMethod =
    | Cash
    | Check(checkNumber);

  // etc.
};
