# frozen_string_literal: true

class Hasher
  def self.fnv1(string, variant: 64, offset_basis: nil)
    prime, offset_basis, pack_template =
      case variant
      when 32 then [16_777_619, offset_basis || 2_166_136_261, 'L']
      when 64
        [1_099_511_628_211, offset_basis || 14_695_981_039_346_656_037, 'Q']
      else raise ArgumentError, "Variant #{variant}-bit not supported"
      end

    string.each_byte.reduce(offset_basis) do |hash, byte|
      [hash * prime].pack(pack_template).unpack1(pack_template) ^ byte
    end
  end
end
