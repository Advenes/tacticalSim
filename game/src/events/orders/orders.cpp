#include "orders.h"

bool MovingOrder::execute(){
    if(unitsFollowing.empty()){
        return false;
    }
    
    for (auto itUnit = unitsFollowing.begin(); itUnit != unitsFollowing.end(); ) {
        auto& unit = itUnit->first;
        auto& pointIt = itUnit->second;

        if (unit->getCurrentOrder() != this) {
            itUnit = unitsFollowing.erase(itUnit);
            continue;
        }

        MovePoint& targetPoint = *pointIt;

        if (int(unit->getPosition().x) == targetPoint.x && int(unit->getPosition().y) == targetPoint.y) {
            std::cout << "finished walking to a point" << '\n';
            ++pointIt;

            if (pointIt == points.end()) {
                itUnit = unitsFollowing.erase(itUnit);
                continue;
            }
        }

        if (pointIt != points.end()) {
            Position current = unit->getPosition();
            float dx = pointIt->x - current.x;
            float dy = pointIt->y - current.y;

            float stepX = (dx == 0) ? 0 : (dx > 0 ? 0.05f : -0.05f) * unit->values.speed;
            float stepY = (dy == 0) ? 0 : (dy > 0 ? 0.05f : -0.05f) * unit->values.speed;;

            stepX *= (static_cast<int>(getSpeed()) + 1);
            stepY *= (static_cast<int>(getSpeed()) + 1);

            unit->setPosition({ current.x + stepX, current.y + stepY });
        }

        ++itUnit;
    }
    return true;
}


bool AttackOrder::execute(){
    for (auto itUnit = unitsFollowingAndAttacked.begin(); itUnit != unitsFollowingAndAttacked.end();) {
        Unit* unit = itUnit->first;
        if (unit->getCurrentOrder() != this || unit->getCurrentOrder() == nullptr) {
            itUnit = unitsFollowingAndAttacked.erase(itUnit);
            continue;
        }
        itUnit++;
    }

    if(unitsFollowingAndAttacked.empty()){
        return false;
    }

    if (GameTime::get().getTime() % 60 != 0) {
        return true;
    }

    for (auto& attackerPair : unitsFollowingAndAttacked) {

        Unit* attacker = attackerPair.first;
        Unit* defender = attackerPair.second;
std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dice(0.5f, 2.5f); // simulates random roll (0.5x–1.5x effectiveness)

    Vector2 distance = {float(abs(defender->getPosition().x - attacker->getPosition().x)), float(abs(defender->getPosition().y - attacker->getPosition().y))};

    int softAttack = attacker->values.softAttack;
    int hardAttack = attacker->values.hardAttack;

    // --- Random dice rolls for both sides ---
    float attackRoll = dice(gen);
    float defenseRoll = dice(gen);

    // --- Attacking side's combat multiplier ---
    float attackMultiplier =
        (attacker->values.organization / 10.0f)
        + (softAttack * (1.0f - defender->values.hardness / 100.0f))
        + (hardAttack * (defender->values.hardness / 100.0f))
        + (attacker->values.morale / 10.0f)
        + ((100.0f - attacker->values.exhaustion) / 100.0f) * 10.0f
        + (attacker->values.ammo / 10.0f);


    int attackerLoc = static_cast<int>(attacker->getLevelOfCommand());
    int defenderLoc = static_cast<int>(defender->getLevelOfCommand());

    float locAmplifier = std::pow(4.0f, static_cast<float>(attackerLoc - 1)) / std::pow(4.0f, static_cast<float>(defenderLoc - 1));
    attackMultiplier *= locAmplifier;
    attackMultiplier *= attackRoll;

    // --- defender counterattack potential ---
    float defensePower =
        (defender->values.organization / 10.0f)
        + (defender->values.softAttack * (1.0f - attacker->values.hardness / 100.0f))
        + (defender->values.hardAttack * (attacker->values.hardness / 100.0f))
        + (defender->values.morale / 10.0f)
        + ((100.0f - defender->values.exhaustion) / 100.0f) * 10.0f
        + (defender->values.ammo / 10.0f);

    locAmplifier = std::pow(4.0f, static_cast<float>(defenderLoc - 1)) / std::pow(4.0f, static_cast<float>(attackerLoc - 1));
    defensePower *= locAmplifier;
    defensePower *= defenseRoll;

    // --- Apply results ---
    float defenderDamage = (attackMultiplier * 0.01f) / defenderLoc;
    float attackerDamage = (defensePower * 0.01f) / attackerLoc;

    // defender takes hits
    defender->values.organization -= defenderDamage;
    defender->values.morale -= defenderDamage * 1.5f;
    defender->values.exhaustion += defenderDamage * 1.0f;

    // attacker may take some return fire
    attacker->values.organization -= attackerDamage;
    attacker->values.morale -= attackerDamage;
    attacker->values.exhaustion += attackerDamage * 1.5f;

    // Clamp values to sane ranges
    auto clamp = [](int& v, float min, float max){ v = std::clamp(float(v), min, max); };
    clamp(defender->values.organization, 0.0f, 100.0f);
    clamp(defender->values.morale, 0.0f, 100.0f);
    clamp(defender->values.exhaustion, 0.0f, 100.0f);
    clamp(attacker->values.organization, 0.0f, 100.0f);
    clamp(attacker->values.morale, 0.0f, 100.0f);
    clamp(attacker->values.exhaustion, 0.0f, 100.0f);

    // --- Combat log ---
    std::cout << "=== Combat Round ===\n";
    std::cout << "Attack roll: " << attackRoll << ", Defense roll: " << defenseRoll << "\n";
    std::cout << "attacker deals: " << defenderDamage << " | defender deals: " << attackerDamage << "\n";
    std::cout << "defender Org: " << defender->values.organization
              << ", Morale: " << defender->values.morale
              << ", Exhaustion: " << defender->values.exhaustion << "\n";
    std::cout << "attacker Org: " << attacker->values.organization
              << ", Morale: " << attacker->values.morale
              << ", Exhaustion: " << attacker->values.exhaustion << "\n";
    }

    return true;
}
