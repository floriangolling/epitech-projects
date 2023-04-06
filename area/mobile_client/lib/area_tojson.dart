import 'dart:core';

import 'package:area/actions_class.dart';
import 'package:area/reactions_class.dart';

class AreaToJson {
  Actions? currentAction;

  bool checkIfActionIsNull() {
    return [currentAction?.description, currentAction?.name, currentAction?.serviceName].contains(null);
  }

  Reactions? currentReaction;

  bool checkIfReactionIsNull() {
    return [currentReaction?.description, currentReaction?.name, currentReaction?.serviceName].contains(null);
  }

  static final AreaToJson _singleton = AreaToJson._internal();

  factory AreaToJson() => _singleton;

  AreaToJson._internal(); // private constructor
}
