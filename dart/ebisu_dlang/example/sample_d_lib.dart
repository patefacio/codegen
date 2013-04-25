import 'dart:io';
import 'dart:json' as JSON;
import 'package:ebisu/ebisu_id.dart';
import 'package:ebisu/ebisu_utils.dart';
import 'package:ebisu_dlang/meta.dart';

main() {
  
  Constant taxTable(name, init) {
    return constant(name)
      ..type = 'TaxTable'
      ..hasStaticThis = true
      ..init = init;
  }

  Package pkg = package('forecast')
    ..modules = [
      module('income_expense_model')
      ..imports = [
        'datetime',
        'plusauri.statement.ies',
        'plusauri.tvm.cflow',
        'opmix.mix',
        'pprint.pp'
      ]
      ..publicImports = [ 'plusauri.date_range' ]
      ..debugImports = [ 'stdio' ]
      ..unitTest = true
      ..structs = [
        struct('modeled_item_spec')
        ..members = [
          member('label')..access = Access.RO,
          member('type')..access = Access.RO ..type='IESType',
          member('spec')..access = Access.RO ..type='CFlowSequenceSpec'
        ],
        struct('modeled_item')
        ..members = [
          member('label')..access = Access.RO,
          member('type')..access = Access.RO ..type='IESType',
          member('c_flows')..access = Access.RO ..type='CFlowSequence',
          member('growth')..access = Access.RO ..type='double' ..init = 0
        ],
        struct('income_expense_model')
        ..doc = '''

Model income and expenses not covered by basic growth/dividend assumptions on
balance sheet items. For example, you might want to model in future
anticipated medical expense. On the income side, maybe there is an anticipated
inheritance. This would not require a balance sheet item, but rather a modeled
series of expenses. With this scheme any one time or series of anticipated
income or expenses may be included in the financial planning.

'''
        ..aliases = [
          arr('modeled_item_spec'),
          arr('modeled_item'),
        ]
        ..members = [
          member('modeled_item_arr')
        ]
        
      ],
      module('taxes')
      ..imports = [
        'plusauri.statement.enums',
        'plusauri.statement.ies',
        'plusauri.statement.balance_sheet',
        'plusauri.tax.table',
        'plusauri.rmap',
        'opmix.mix',
        'pprint.pp',
      ]
      ..debugImports = [ 'stdio' ]
      ..publicSection = true
      ..constants = [
        constant('qualified_dividend_2011')
        ..type = 'TaxTable'
        ..hasStaticThis = true
        ..init = '''TaxTable(TaxType.QualifiedDividend,
  TableEntry(0.0, 0.15),
)
''',
        taxTable('long_term_capital_gains_2011', '''
TaxTable(TaxType.FedLongTermCapitalGain,
  TableEntry(0.0, 0.15),
)
'''),
        taxTable('social_security_2011', '''TaxTable(TaxType.SocialSecurity,
  TableEntry(0.0, 0.062),
  TableEntry(110_100, 0.0),
)
'''),
        taxTable('medicare_2011', '''TaxTable(TaxType.Medicare,
  TableEntry(0.0, 0.0145),
)
'''),
        taxTable('single_2011', '''TaxTable(TaxType.FedOrdinaryIncome,
  TableEntry(0, 0.1),
  TableEntry(8_500, 0.15),
  TableEntry(34_500, 0.25),
  TableEntry(83_600, 0.28),
  TableEntry(174_400, 0.33),
  TableEntry(379_150, 0.35),
)
'''),
        taxTable('married_jointly_2011', '''TaxTable(TaxType.FedOrdinaryIncome,
  TableEntry(0, 0.1),
  TableEntry(17_000, 0.15),
  TableEntry(69_000, 0.25),
  TableEntry(139_350, 0.28),
  TableEntry(212_300, 0.33),
  TableEntry(379_150, 0.35),
)
'''),
        taxTable('married_separately_2011', '''TaxTable(TaxType.FedOrdinaryIncome,
TaxTable(TaxType.FedOrdinaryIncome,
  TableEntry(0, 0.1),
  TableEntry(8_500, 0.15),
  TableEntry(34_500, 0.25),
  TableEntry(69_675, 0.28),
  TableEntry(106_150, 0.33),
  TableEntry(189_575, 0.35),
)'''),
        taxTable('head_of_household_2011', '''TaxTable(TaxType.FedOrdinaryIncome,
  TableEntry(0, 0.1),
  TableEntry(12_150, 0.15),
  TableEntry(46_250, 0.25),
  TableEntry(119_400, 0.28),
  TableEntry(193_350, 0.33),
  TableEntry(379_150, 0.35),
)'''), 
        constant('no_op_tax_assessor')..type = 'TaxAssessor'..init = '{}',
        constant('married_jointly_tax_assessor')
        ..hasStaticThis = true
        ..type = 'TaxAssessor'
        ..init = '''TaxAssessor(
[ 
  MarriedJointly2011.gdup,
  QualifiedDividend2011.gdup,
  LongTermCapitalGains2011.gdup,
  SocialSecurity2011.gdup,
  Medicare2011.gdup
]
)''',
      ]
      ..aliases = [
        alias('taxable_item_basis_rmap')
        ..aliased = 'ReductionMap!(TaxableItem, double)'
        ..doc = 'Maps the breakdown of the bases for each taxable item type'
      ]
      ..structs = [
        struct('tax_assessor')
        ..publicSection = true
        ..privateSection = true
        ..aliases = [ arr('tax_table') ]
        ..members = [
          member('tax_table_arr')..access = Access.RO
          ..doc = 'Tax tables to apply to some set taxable items'
        ]
      ],
      module('forecaster')
      ..doc = 'Support for forecasting a balance sheet forward in time'
      ..publicSection = true
      ..publicImports = [ 'plusauri.forecast.taxes' ]
      ..imports = [ 'datetime', 'traits', 'stdio', 'typecons', 'conv', 
        'algorithm', 'exception',
        'plusauri.statement.balance_sheet',
        'plusauri.statement.constants',
        'plusauri.statement.transact',
        'plusauri.statement.ies',
        'plusauri.forecast.iem',
        'plusauri.tvm.cflow',
        'plusauri.tvm.rcurve',
        'plusauri.tvm.pvf',
        'plusauri.date_range',
        'plusauri.tax.table',
        'opmix.mix',
        'pprint.pp',
      ]
      ..constants = [ 
        constant('no_forecast')..type = 'Forecast',
        constant('tax_type_to_i_e_type')..type = 'IESType[TaxType.max - TaxType.min + 1]'
      ]
      ..structs = [
        struct('forecaster')
        ..doc = 'Given a balance sheet and various hooks, forecasts valuations.'
        ..publicSection = true..privateSection=true
        ..aliases = [ arrAlias('tax_table')..immutable = false ]
        ..members = [
          member('inflation')
          ..doc = 'Curve for inflation'
          ..type = 'RateCurve'
          ..ctor = true
          ..byRef = true,
          member('tax_assessor')
          ..doc = 'For calculating taxes through the years'
          ..ctorDefaulted = true
          ..init = 'NoOpTaxAssessor'
          ..byRef = true,
          member('income_expense_model')
          ..doc = 'For additional income/expenses beyond simple growth of assets and liabilities'
          ..ctorDefaulted = true
          ..init = 'NoIncomeExpense'
          ..byRef = true
        ],
        struct('forecast')
        ..doc = 'The result of applying a Forecaster to a balance sheet on a specific period'
        ..privateSection = true
        ..members = [
          member('period_balance_sheet')
          ..doc = 'Captures the change over a forecast period of all items in the balance sheet',
          member('i_e_statement')
          ..doc = 'Income/expense statement over the forecast period'
        ]
      ]
    ];

  print(prettyJsonMap(pkg));

}