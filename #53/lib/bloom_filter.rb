# frozen_string_literal: true

require 'bit_array'
require 'hasher'

class BloomFilter
  attr_reader :size, :hash_function_count, :version

  def initialize(
    element_count,
    epsilon: 0.01,
    version: 0
  )
    data =  element_count.is_a?(String) ? load_from_file(element_count) : []

    @size = data[2] || required_bit_qty(element_count, epsilon)
    @hash_function_count =
      data[1] || optimal_hash_function_qty(@size, element_count)
    @bit_array = BitArray.new(data[3] || @size, bits_per_item: 8)
    @version = data[0] || version
  end

  # def to_i
  #   @bit_array.to_s.to_i(2)
  # end

  def add(string)
    compute_64bit_fnv1_hashes(string.strip)
      .each { |hash| @bit_array[hash] = 1 }
  end

  def include?(string)
    return false if string.empty?

    compute_64bit_fnv1_hashes(string.strip)
      .map { |hash| @bit_array[hash] }
      .none?(0)
  end

  def save_to_file(filepath)
    @version += 1

    File.open("#{filepath}.bf", 'w') do |file|
      file << build_header
      @bit_array.each_byte do |byte|
        file << [byte].pack('C')
      end
    end
  end

  private

  def required_bit_qty(elem_qty, epsilon)
    -(elem_qty * Math.log(epsilon) / (Math.log(2)**2)).floor
  end

  def optimal_hash_function_qty(bit_qty, elem_qty)
    (bit_qty / elem_qty.to_f * Math.log(2)).ceil
  end

  def compute_64bit_fnv1(string, offset_basis = nil)
    Hasher.fnv1(string, variant: 64, offset_basis: offset_basis)
  end

  def compute_64bit_fnv1_hashes(string)
    return [] if string.empty?

    hashes = []
    offset_basis = nil

    @hash_function_count.times do
      new_hash = compute_64bit_fnv1(string, offset_basis)
      offset_basis = new_hash
      hashes << (new_hash % @size)
    end

    hashes
  end

  def build_header
    [1_128_481_350, @version, @hash_function_count, @size].pack('NnnN')
  end

  def load_from_file(filepath)
    bytes = File.read(filepath).unpack('NnnNC*')
    bytes[0] == 1_128_481_350 or raise(
      ArgumentError,
      'Invalid header. Should start with CCBF'
    )

    [bytes[1], bytes[2], bytes[3], bytes[4..]]
  end

  alias << add
  alias === include?
end
