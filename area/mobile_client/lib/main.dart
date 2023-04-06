import 'package:area/account_page.dart';
import 'package:area/choose_action_reaction.dart';
import 'package:area/choose_service.dart';
import 'package:area/homepage.dart';
import 'package:area/recap_action_page.dart';
import 'package:area/select_action_page.dart';
import 'package:flutter/material.dart';
import 'login_screen.dart';

void main() {
  runApp(const Area());
}

Map<String, WidgetBuilder> routes = {
  '/login': (context) => const LoginScreen(),
  '/': (context) => const HomePage(),
  ChooseActionReaction.routeName: (context) => const ChooseActionReaction(),
  ChooseService.routeName: (context) => const ChooseService(),
  SelectActionPage.routeName: (context) => SelectActionPage(),
  RecapActionPage.routeName: (context) => const RecapActionPage(),
  AccountPage.routeName: (context) => const AccountPage(),
};

class Area extends StatelessWidget {
  const Area({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      routes: routes,
      initialRoute: "/login",
    );
  }
}
