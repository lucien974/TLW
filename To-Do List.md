# Code rewriting/review
## Change for a more explicit name
- [ ] Bloon::touch
- [ ] Entity::getLastSprite
- [ ] Entity::spriteStatus
- [ ] void Level::event
- [ ] class Multitower
- [ ] Multitower::m_up/Multitower::m_up_price/Multitower::m_select
- [ ] class Textureloader [Not only texture are manipulated]
- [ ] Vague::next
- [ ] Vague::size

## Translating
- [ ] class Bouton
- [ ] Bouton::doubleBouton
- [ ] Bouton::affiche
- [ ] class Multitower to MultiTower
- [ ] Tower::getBullet [to getBulletPosition?
- [ ] Tower::getNumberBullet [to getBulletNumber]

## Modify to ```const``` method
For instance: ```int getSize();``` to ``` int getSize() const;```
- [ ] Bloon::getMoney
- [ ] Bouton::isInside
- [ ] Bouton::affiche
- [ ] Entity::isNearOf
- [ ] Entity::isColliding
- [ ] Textureloader::getTexture [References should be const too]
- [ ] Textureloader::getBuffer [References should be const too]
- [ ] Textureloader::getFont [References should be const too]
- [ ] Textureloader::getMap [References should be const too]
- [ ] Textureloader::getRedPxl
- [ ] Tower::getCost
- [ ] Tower::getUpPrice
- [ ] Vague::getBloon

## Logical problems
- [ ] Bullet::move [drawing should not be make in move method]

## To review
- [ ] Bouton::isInside
- [ ] class Carre [useless ?]
- [ ] class Point [useless ?]
- [ ] class Interface [Put interface code in Interface class]
- [ ] **bool** getGlobalBounds
- [ ] Entity::drawRange [unrelated content with method's name]
- [ ] Tower::drawBullet

## Miscellaneous
- [ ] class Bouton should inherit from sf::Drawable
- [ ] Bouton::set/Bouton::setup/Bouton::Bouton [Differences between these three methods]

### To discuss
- [ ] A class IceTower which inherit from Tower
- [ ] File which defines constants
