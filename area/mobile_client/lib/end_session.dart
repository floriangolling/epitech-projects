import 'login_screen.dart';
import 'package:flutter/material.dart';

// ignore: non_constant_identifier_names
void EndSession(BuildContext context) async {
  await storage.deleteAll();
  Navigator.of(context)
      .pushNamedAndRemoveUntil('/login', (Route<dynamic> route) => false);
}
